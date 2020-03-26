package main

import (
	"encoding/json"
	"fmt"
)

import "gofc/variant"

func main() {
	v := variant.NewVariant(1.5)
	fmt.Println(v.Str)
	b, _ := json.Marshal(v)
	fmt.Println(string(b))

	v.SetString("xxwdfljksakdljskald!")
	fmt.Println(v.Str)

	b, _ = json.Marshal(v)
	fmt.Println(string(b))
}
