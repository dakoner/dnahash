package main

import (
	"fmt"
)

func base_to_bits(a byte) uint16 {
	switch a {
	case 'A':
		return 0
	case 'C':
		return 1
	case 'G':
		return 2
	case 'T':
		return 3
	}
	panic(a)
}

func bits_to_base(a uint16) byte {
	switch a {
	case 0:
		return 'A'
	case 1:
		return 'C'
	case 2:
		return 'G'
	case 3:
		return 'T'
	}
	panic(a)

}

func convert_kmer_to_2bit(s []byte) uint16 {
	var n uint16

	for _, c := range s {
		n <<= 2
		n |= base_to_bits(c)
	}
	return n
}

func convert_2bits_to_kmer(t uint16) []byte {
	var s []byte
	for i := 0; i < 8; i++ {
		var v = t & 0b11
		x := bits_to_base(v)
		s = append(s, x)
		v >>= 2
	}
	return s
}

func main() {
	bs := []byte{'A', 'C', 'G', 'T'}

	for _, c := range bs {
		n := base_to_bits(c)
		fmt.Printf("%c %08b\n", c, n)
	}
	bs2 := []uint16{0, 1, 2, 3}

	for _, b := range bs2 {
		var c2 = bits_to_base(b)
		fmt.Printf(" %08b %c\n", b, c2)
	}

	s := []byte("TTTTTTTT")
	var v = convert_kmer_to_2bit(s)
	fmt.Printf("%s %d\n", s, v)

	t := uint16(65535)
	var s2 = convert_2bits_to_kmer(t)
	fmt.Printf("%d %s", t, s2)
}
