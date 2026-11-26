# IsPurePC-Matching — M1 build
# Windows 默认没有 make；等价命令：python tools/build.py <target>
PY ?= python

.PHONY: all configure check build ld overrides clean

all: check

configure:
	$(PY) tools/configure.py

build:
	$(PY) tools/build.py build

check:
	$(PY) tools/build.py check

overrides:
	$(PY) tools/build.py overrides

ld:
	$(PY) tools/build.py ld

clean:
	$(PY) -c "import shutil,os; [shutil.rmtree(p, ignore_errors=True) for p in ('asm','assets','build/splat')]"
