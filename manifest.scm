(use-modules ((guix profiles) #:select (packages->manifest))
	     ((gnu packages commencement) #:select (gcc-toolchain))
	     ((gnu packages llvm) #:select (clang))
	     ((gnu packages base) #:select (gnu-make))
	     ((gnu packages man) #:select (man-db man-pages)))

(packages->manifest (list gcc-toolchain
			  clang
			  gnu-make
			  man-db
			  man-pages))
