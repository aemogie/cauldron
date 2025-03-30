(use-modules ((guix profiles) #:select (packages->manifest))
	     ((gnu packages gcc) #:select (gcc))
	     ((gnu packages llvm) #:select (clang-toolchain)))

(packages->manifest (list gcc clang-toolchain))
