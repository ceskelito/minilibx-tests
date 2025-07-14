include variables.mk

# Main targets
all: libs examples

libs: colors imglib mlxlib

colors:
	@echo "Building colors library..."
	@$(MAKE) -C $(COLORS_DIR)

imglib:
	@echo "Building imglib library..."
	@$(MAKE) -C $(IMGLIB_DIR)

mlxlib: colors imglib
	@echo "Building mlxlib wrapper..."
	@$(MAKE) -C $(MLXLIBWRAPPER_DIR)

examples: libs
	@echo "Building examples..."
	@$(MAKE) -C examples

clean:
	@echo "Cleaning libraries..."
	@$(MAKE) -C $(COLORS_DIR) clean
	@$(MAKE) -C $(IMGLIB_DIR) clean
	@$(MAKE) -C $(MLXLIBWRAPPER_DIR) clean
	@$(MAKE) -C examples clean

fclean:
	@echo "Full clean..."
	@$(MAKE) -C $(COLORS_DIR) fclean
	@$(MAKE) -C $(IMGLIB_DIR) fclean
	@$(MAKE) -C $(MLXLIBWRAPPER_DIR) fclean
	@$(MAKE) -C examples fclean

re: fclean all

help:
	@echo "MLXLib - Comprehensive MinilibX Wrapper"
	@echo ""
	@echo "Available targets:"
	@echo "  all       - Build all libraries and examples"
	@echo "  libs      - Build all libraries only"
	@echo "  colors    - Build colors library"
	@echo "  imglib    - Build imglib library"
	@echo "  mlxlib    - Build mlxlib wrapper"
	@echo "  examples  - Build examples"
	@echo "  clean     - Clean object files"
	@echo "  fclean    - Clean everything"
	@echo "  re        - Rebuild everything"
	@echo "  help      - Show this help"
	@echo ""
	@echo "Libraries:"
	@echo "  colors/   - Color manipulation and definitions"
	@echo "  imglib/   - Image management utilities"
	@echo "  mlxlib/   - Complete MLX wrapper with events"
	@echo ""
	@echo "Documentation: README_MLXLIB.md"

.PHONY: all libs colors imglib mlxlib examples clean fclean re help