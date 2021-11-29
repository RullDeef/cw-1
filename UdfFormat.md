# UDF - universal data format

UDF - формат описания сцен и их объектов.

---

Пример описания мэша:

```bash
M
v
20.01 24.0 17 # verties
v
-144.04 21 0
...
t
1 2 3 # triangles
t
2 3 4
mat
my-mesh-mat.mat # material file
EM
```

---

Пример описания сцены:

```bash
S
O
10      # id first
mesh 1  # name second
mesh    # data third
M
...
EM
10 20 30 # position
10 20 30 # rotation
10 20 30 # scale
EO
O
11
main camera
camera
C
...
EC
1 2 3
1 2 3
1 2 3
EO
O
12
directional light 1
light
L
...
EL
1 2 3
1 2 3
1 2 3
EO
ES
```
