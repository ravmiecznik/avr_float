```c++
    //INIT	
	char buffer[100];
	cout << "HELLO" << __FILE__ << endl << endl;
```

```c++	
	Rational<uint64_t> R1(3,4);
	cout << "R1: "<< R1.to_str(buffer) << endl;
	cout << "R1: "<< R1.to_float(buffer) << endl;
```

```console
$:	R1: R:3/4 <br>
$:	R1: 0.75
```

```c++
	Rational<uint16_t> R2(1,3);
	cout << "R2: "<< R2.to_str(buffer) << endl;
	cout << "R2: "<< R2.to_float(buffer) << endl;
```

```console
$:	R2: R:1/3
$:	R2: 0.33
```

```c++
	cout << "R1+R2: "<< (R1+(Rational<uint64_t>)R2).to_str(buffer) << endl; //add with cast
	cout << "R1+R2: "<< (R1+(Rational<uint64_t>)R2).to_float(buffer) << endl;
```

```console
$:	R1+R2: R:13/12
$:	R1+R2: 1.08
```

```c++
	cout << "R1+R2: "<< (Ri16(5,3) + Ri16(6,3)).to_str(buffer) << endl;
	cout << "R1+R2: "<< (Ri16(5,3) + Ri16(6,3)).to_float(buffer) << endl;
```

```console
$:	R1+R2: R:11/3
$:	R1+R2: 3.66
```

```c++
	Ri16 R3(5,3);
	R3 += Ri16(6,3);
	cout << "R1+=R2: "<< R3.to_str(buffer) << endl;
	cout << "R1+=R2: "<< R3.to_float(buffer) << endl;
```

```console
$:	R1+=R2: R:11/3
$:	R1+=R2: 3.66
```
