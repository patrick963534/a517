# GNU Make solution makefile autogenerated by Premake
# Type "make help" for usage help

ifndef config
  config=debug
endif
export config

PROJECTS := tsp_demo

.PHONY: all clean help $(PROJECTS)

all: $(PROJECTS)

tsp_demo: 
	@echo "==== Building tsp_demo ($(config)) ===="
	@${MAKE} --no-print-directory -C build -f Makefile

clean:
	@${MAKE} --no-print-directory -C build -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "   debug"
	@echo "   release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   tsp_demo"
	@echo ""
	@echo "For more information, see http://industriousone.com/premake/quick-start"
