This is instruction to run MSI simulation
This simple system has L1 unified cache for each core, based on http://learning.gem5.org/book/part3/MSI/configuration.html

Files:
MSI.py:    Add this file to gem5/configs/ruby
se-msi.py: Add this file to gem5/configs/example


Example:
Assume your MSI build folder is X86_MSI

build/X86_MSI/gem5.opt  configs/example/se-msi.py --num_cpu=4 --l1_size=16kB --l1_assoc=2 --cache_line_size=64  --binary=/YOUR_PATH/critical-fs --thread=4 --ite=100

In this script you would use a system with 4 cores, L1 size 16KB with 2-way assoc, cache line size is 64 bytes. You run critical-fs with 4 threads and 100 iterations.

