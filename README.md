# 🗃 Containers

Reimplementing some stl containers

## 🗄️ Containers:

- [Vector]
- [Deque]
- [Stack]
- [Map]
- [Set]

## 🖇️ Features:
- Iterators
- Iterator traits
- enable_if
- Type traits

## 🪴 Implementation:
`Deque` is implemented as a [circular buffer](https://en.wikipedia.org/wiki/Circular_buffer)  
`Map` and `Set` are both implemented as a [red-black tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree)

## 📊 Bench mark results:
I ran benchmarks on all my containers with my own tester which can be found [here](https://github.com/K1ngmar/Container-Tester)

### Vector:
![vector benchmark](./vector/vector_benchmark.png)

### Deque:
![deque benchmark](./deque/deque_benchmark.png)

### Map:
![map benchmark](./map/map_benchmark.png)

### Set:
![set benchmark](./set/set_benchmark.png)
