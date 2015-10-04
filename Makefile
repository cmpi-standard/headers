# ------------------------------------------------------------------------------
# Makefile for GitHub project cmpi-wg/cmpi-headers
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
#
# It is assumed that the GitHub project cmpi-wg/cmpi-wg.github.io has its work
# directory in the location specified by the github_pages_work_dir variable.
# ------------------------------------------------------------------------------

# Current CMPI version in m.n.u format.
# Keep in sync with the CMPI header files
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
doxygen_css_file := resources/doxygen_cmpi.css

# Doxygen mainpage file.
# Keep in sync with USE_MDFILE_AS_MAINPAGE parameter in Doxyfile
doxygen_mainpage_file := mainpage.md

# Doxygen command and any options
doxygen_cmd := doxygen

# Generated CMPI API ZIP file with Doxygen HTML output
cmpi_api_html_zip_file := cmpi_$(cmpi_version)_api_html.zip

# Generated CMPI headers ZIP file
cmpi_headers_zip_file := cmpi_$(cmpi_version)_headers.zip

# CMPI header files
cmpi_headers := cmpift.h cmpidt.h cmpios.h cmpipl.h cmpimacs.h

# No built-in rules needed
.SUFFIXES:

.PHONY: build publish clean all help

build_files := $(cmpi_headers_zip_file) $(cmpi_api_html_zip_file)

build: $(build_files)
	@echo 'Makefile: $@ done; created: $(build_files)'

publish: $(github_pages_unpack_dir) build
	test -d $(github_pages_unpack_dir)/api
	test -d $(github_pages_unpack_dir)/files
	sh -c 'cd $(github_pages_unpack_dir)/api; rm -rf *'
	unzip -qo -d $(github_pages_unpack_dir)/api $(cmpi_api_html_zip_file)
	cp -p $(cmpi_api_html_zip_file) $(github_pages_unpack_dir)/files/
	cp -p $(cmpi_headers_zip_file) $(github_pages_unpack_dir)/files/
	@echo 'Makefile: $@ done; published to: $(github_pages_unpack_dir)'

clean:
	rm -rf doxygen
	@echo 'Makefile: $@ done.'

clobber: clean
	rm -f $(build_files)
	@echo 'Makefile: $@ done.'

all: build publish clean
	@echo 'Makefile: $@ done.'

help:
	@echo 'Makefile for CMPI headers project'
	@echo 'Valid targets are:'
	@echo '  build   - (default) Build the API and header zip files.'
	@echo '  publish - Publish the API and header zip files to CMPI pages project.'
	@echo '  clean   - Remove any temporary files.'
	@echo '  clobber - Remove any temporary files and build products.'
	@echo '  all     - build, publish, clean'

# CMPI API ZIP file with Doxygen HTML output
# Because it is hard to capture all generated HTML files, they are considered
# an intermediate product (= temporary files) and the zip file picking them up
# is considered the build product.
$(cmpi_api_html_zip_file): $(cmpi_headers) Doxyfile resources/*.png $(doxygen_css_file) \
		$(doxygen_mainpage_file) modules.dox
	mkdir -p $(doxygen_html_out_dir)
	sh -c 'cd $(doxygen_html_out_dir); rm -rf *'
	$(doxygen_cmd)
	sh -c 'cd $(doxygen_html_out_dir); zip -qru $(doxygen_html_out_updir)/$(cmpi_api_html_zip_file) .'

# CMPI headers ZIP file.
$(cmpi_headers_zip_file): $(cmpi_headers)
	zip -qu $(cmpi_headers_zip_file) $(cmpi_headers)
