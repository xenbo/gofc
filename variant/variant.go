package variant

//#cgo CXXFLAGS: -std=c++14  -I include
//#cgo CFLAGS:  -I include
//#cgo linux  LDFLAGS:  -lstdc++
//#cgo darwin LDFLAGS:  -lc++
//#include "export_c.h"
import "C"
import (
	"reflect"
	"unsafe"
)

type Variant struct {
	iv     *C.govariant
	TypeId int
	Str    string
}

func NewVariant(f interface{}) Variant {
	v := Variant{}

	t := reflect.ValueOf(f).Type()
	kind := t.Kind()

	switch kind {
	case reflect.Bool:

	case reflect.Int, reflect.Int8, reflect.Int16, reflect.Int32:
		v.SetInt(f.(int))
	case reflect.Int64:
		v.SetInt64(f.(int64))
	case reflect.Uint, reflect.Uint8, reflect.Uint16, reflect.Uint32:
		v.SetUInt(f.(uint))
	case reflect.Uint64:
		v.SetUInt64(f.(uint64))
	case reflect.Float32:
		v.SetFloat32(f.(float32))
	case reflect.Float64:
		v.SetFloat64(f.(float64))
	case reflect.String:
		v.SetString(f.(string))
	case reflect.Slice: //TODO...
		v.SetString(string(f.([]byte)))
	case reflect.Map: //TODO...

	case reflect.Struct:

	case reflect.Ptr:

	}

	return v
}

func (v *Variant) SetInt(f int) {
	v.iv = C.SetInt(C.int(f))
	v.Str = C.GoString(C.ToString(v.iv))
	v.TypeId = int(C.GetType(v.iv))
}

func (v *Variant) SetInt64(f int64) {
	v.iv = C.SetInt64(C.longlong(f))
	v.Str = C.GoString(C.ToString(v.iv))
	v.TypeId = int(C.GetType(v.iv))
}

func (v *Variant) SetUInt(f uint) {
	v.iv = C.SetuInt(C.uint(f))
	v.Str = C.GoString(C.ToString(v.iv))
	v.TypeId = int(C.GetType(v.iv))
}

func (v *Variant) SetUInt64(f uint64) {
	v.iv = C.SetuInt64(C.ulonglong(f))
	v.Str = C.GoString(C.ToString(v.iv))
	v.TypeId = int(C.GetType(v.iv))
}

func (v *Variant) SetFloat32(f float32) {
	v.iv = C.SetFloat(C.float(f))
	v.Str = C.GoString(C.ToString(v.iv))
	v.TypeId = int(C.GetType(v.iv))
}

func (v *Variant) SetFloat64(f float64) {
	v.iv = C.SetDouble(C.double(f))
	v.Str = C.GoString(C.ToString(v.iv))
	v.TypeId = int(C.GetType(v.iv))
}

func (v *Variant) SetString(f string) {
	v.iv = C.SetString(C.CString(f), C.int(len(f)))
	//v.Str = C.GoString(C.ToString(v.iv))

	b, l:= v.AsString()
	v.Str = string(b[0:l])
	v.TypeId = int(C.GetType(v.iv))
}

func (v *Variant) AsInt() int {
	return int(C.GetInt(v.iv))

}

func (v *Variant) AsInt64() int64 {
	return int64(C.GetInt64(v.iv))
}

func (v *Variant) AsUInt() uint {
	return uint(C.GetuInt(v.iv))
}

func (v *Variant) AsUInt64() uint64 {
	return uint64(C.GetuInt64(v.iv))
}

func (v *Variant) AsFloat32() float32 {
	return float32(C.GetFloat(v.iv))
}

func (v *Variant) AsFloat64() float64 {
	return float64(C.GetDouble(v.iv))
}

func (v *Variant) AsString() ([]byte, int) {
	var bytes = make([]byte, 1024)
	len := C.GetString(v.iv, unsafe.Pointer(&bytes[0]), C.int(len(bytes)))
	return bytes, int(len)
}
