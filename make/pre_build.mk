
# Create required directories
pre_build:
	@mkdir -p $(CUR_BUILDDIR)/$(OUT_DIR)
	-@echo "Created directory: $(CUR_BUILDDIR)/$(OUT_DIR)"
	-@echo ' '

.PHONY: pre_build