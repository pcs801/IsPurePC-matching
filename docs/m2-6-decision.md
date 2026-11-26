# M2.6 决策：全面转逐函数 LLM worker（全量，不试点）

> 日期：2026-11-26。用户决定：不做 50 个试点，直接全量转逐函数 worker。

## 队列

- 范围：剩余 **3,743** 个未匹配函数（3,966 - 223）
- 排序：按 `build/hard-classes.json` 的工作类别，**先易后难**
  1. 无分支、调用 ≤1、size ≤64
  2. 分支 ≤3、调用 ≤3、size ≤128
  3. 其余
  4. 特殊指令（likely/unaligned/FPU/syscall）放最后
- 排除：SDK 库函数（not-ours）、编译器内置

## 批处理

- 批大小：**50 个/批**
- 每批结束：写 `build/m26-batch-N.json`（命中/未命中/token）、更新 ledger、跑 `make progress`
- 批间不等待人工确认（全量连续跑）

## 三个保险（必须实现）

1. **命中率门禁**：连续 **2 批**命中率 <15% → 自动暂停，写 `docs/m2-6-stall.md` 并停
2. **token 上限**：每批 token 上限 40M（50 函数 × 0.8M），超限即停
3. **失败归档**：单函数重试 ≤30 次，仍失败 → `known-hard`，不阻塞队列

## 预算预期

- 3,743 函数 × 0.5M ≈ **1.9B tokens**（乐观）
- 3,743 × 0.8M ≈ **3.0B tokens**（悲观）
- 若命中率 40%，有效成本约 5M tokens/命中函数

## 停止条件（任一）

1. 队列跑完
2. 命中率门禁触发
3. token 预算耗尽
4. 用户叫停

## 产出

- `tools/worker_match.py`：一函数一沙箱，证据卡 → LLM → 编译 → 匹配 → 重试
- `build/m26-queue.json`：3,743 个函数的有序队列
- `docs/m2-6-worker.md`：最终统计（命中率、token、known-hard 清单）
