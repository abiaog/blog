#/bin/bash
wget \
	--recursive \
	--no-clobber \
	--page-requisites \
	--html-extension \
	--convert-links \
	--restrict-file-names=windows \
	--domains kernel.org \
	--no-parent \
	https://www.kernel.org/doc/gorman/html/understand/
