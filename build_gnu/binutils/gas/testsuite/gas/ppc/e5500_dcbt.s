# Power E5500 dcbt tests
	.section ".text"
start:
	dcbt	0, 0, 5
	dcbtst	0, 0, 5
