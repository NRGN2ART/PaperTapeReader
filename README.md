# PaperTapeReader
Paper tape reader information, Arduino UNO Code, scripts, documentation

sketch_paper_tape_reader.ino  -> This is an Arduino UNO program to interface the paper tape reader

process_tape_nova  -> This is an example python script to process tape hex data and interpret it in 
                      Data General Nova OBJ format. Only supports basic data blocks. Need to add support for repeated data which so far my tapes dont use (yet).
                      For reference see SIMH project NOVA/nova_sys.c (https://github.com/open-simh/simh/blob/master/NOVA/nova_sys.c) "Binary Loader"

tape_pdp8_spacewar_read1.txt        -> Example tape read- PDP8 Space War 
tape_pdp8_mem_check_high_read1.txt  -> Example read tape - PDP8 utility
tape_pdp8_mem_check_high_read2.txt  -> Same as above but a second capture

Video of reading a paper tape via this Arduino UNO interface:
   https://www.youtube.com/shorts/PvraiOrcCRk
   
This project was inspired by : https://www.youtube.com/watch?v=dq2EuooRrVc

I obtained a similar Remex reader. It had a bad power supply which I had to bypass to get working.

I chose to use an Arduino UNO R3 for interfacing as it is nativly 5V


Andrew Seawright
