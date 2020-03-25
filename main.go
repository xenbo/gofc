package main

import "fmt"

import "gofc/variant"

func main(){

	v := variant.NewVariant(1.5)
	fmt.Println(v.AsFloat32())

	v.SetString("xxwdfljksakdljskald")
	str, _:=v.AsString()
	fmt.Println(string(str))
}
