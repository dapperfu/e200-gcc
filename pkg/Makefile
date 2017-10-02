.DEFAULT: all
.PHONY:
all: binutils-2.24.90.tar.bz2 cloog-0.18.1.tar.gz expat-2.1.0.tar.gz gettext-0.19.4.tar.xz

binutils-2.24.90.tar.bz2:
	wget https://www.mirrorservice.org/sites/sourceware.org/pub/binutils/snapshots/binutils-2.24.90.tar.bz2

cloog-0.18.1.tar.gz:
	wget http://ftp.nluug.nl/languages/gcc/infrastructure/cloog-0.18.1.tar.gz

expat-2.1.0.tar.gz:
	wget --output-file=$@ https://sourceforge.net/projects/expat/files/expat/2.1.0/expat-2.1.0.tar.gz/download


gettext-0.19.4.tar.xz:
	wget --output-file=$@ https://ftp.gnu.org/gnu/gettext/gettext-0.19.4.tar.xz
