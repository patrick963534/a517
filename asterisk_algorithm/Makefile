# GNU Make solution makefile autogenerated by Premake
# Type "make help" for usage help

ifndef config
  config=debug
endif
export config

PROJECTS := asterisk_algorithm

.PHONY: all clean help $(PROJECTS)

all: $(PROJECTS)

asterisk_algorithm: 
	@echo "==== Building asterisk_algorithm ($(config)) ===="
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
	@echo "   asterisk_algorithm"
	@echo ""
	@echo "For more information, see http://industriousone.com/premake/quick-start"
