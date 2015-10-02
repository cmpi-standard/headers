# ------------------------------------------------------------------------------
# Makefile for GitHub project cmpi-wg/cmpi-headers.git
#
# Supported platforms for this makefile:
#   Linux
#   Not tested on Windows, may work when using CygWin
#
# Prerequisites:
#   make (GNU make)
#   doxygen 1.8.2 or higher
#   sh, echo, cd, test, rm, mkdir
#   zip, unzip
# ------------------------------------------------------------------------------

# CMPI version in m.n.u format
cmpi_version := 2.1.0

# Work directory of corresponding GitHub pages project
github_pages_work_dir := ../cmpi-wg.github.io.git

# Unpack location for Doxygen HTML ZIP file within GitHub pages project
github_pages_unpack_dir := $(github_pages_work_dir)/cmpi-releases/$(cmpi_version)

# Doxygen HTML output directory in this project.
# Keep in sync with HTML_OUTPUT parameter in Doxyfile
doxygen_html_out_dir := doxygen/html
doxygen_html_out_updir := ../..

# Doxygen extra CSS stylesheet file.
# Keep in sync with HTML_EXTRA_STYLESHEET parameter in Doxyfile
doxygen_css_file := doxygen_cmpi.css

# Doxygen mainpage file.
# Keep in sync with USE_MDFILE_AS_MAINPAGE parameter in Doxyfile
doxygen_mainpage_file := mainpage.md

# Generated Doxygen HTML ZIP file
doxygen_html_zip_file := doxygen_html.zip

# Doxygen command and any options
doxygen_cmd := doxygen


# No built-in rules needed
.SUFFIXES:

.PHONY: build publish clean all help

build: $(doxygen_html_zip_file)
	@echo 'Makefile: $@ done; created: $(doxygen_html_zip_file)'

publish: $(github_pages_unpack_dir) build
	test -d $(github_pages_unpack_dir)
	sh -c 'cd $(github_pages_unpack_dir); rm -rf *'
	unzip -qo -d $(github_pages_unpack_dir) $(doxygen_html_zip_file)
	@echo 'Makefile: $@ done; published to: $(github_pages_unpack_dir)'

clean:
	rm -rf doxygen
	@echo 'Makefile: $@ done.'

clobber: clean
	rm -f $(doxygen_html_zip_file)
	@echo 'Makefile: $@ done.'

all: build publish clean
	@echo 'Makefile: $@ done.'

help:
	@echo 'Makefile for CMPI headers project'
	@echo 'Valid targets are:'
	@echo '  build   - (default) Build the Doxygen HTML zip file: $(doxygen_html_zip_file)'
	@echo '  publish - Publish the Doxygen HTML files to: $(github_pages_unpack_dir)'
	@echo '  clean   - Remove any temporary files.'
	@echo '  clobber - Remove any temporary and generated files.'
	@echo '  all     - build, publish, clean'

# Documentation for package (generates more .html files than just this target)
$(doxygen_html_zip_file): Doxyfile cmpi*.h resources/*.png $(doxygen_css_file) \
		$(doxygen_mainpage_file) modules.dox
	mkdir -p $(doxygen_html_out_dir)
	sh -c 'cd $(doxygen_html_out_dir); rm -rf *'
	$(doxygen_cmd)
	sh -c 'cd $(doxygen_html_out_dir); zip -qru $(doxygen_html_out_updir)/$(doxygen_html_zip_file) .'
