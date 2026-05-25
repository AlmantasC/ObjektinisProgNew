# ObjektinisProg

## Naudojimosi instrukcija

Funkcijos:
- Pasirinktinas išvestis į failą arba į terminalą.
- Pasirinktinas galutinio rezultato skaičiavimas, remiantis vidurkiu arba mediana.
- Rūšiavimas pasirinktinu būdu.
- Studentų skirstymas į „nevykelius" (galutinis < 5) ir „nerdus" (galutinis ≥ 5).

```
1 parinktis - rankinis duomenų įvedimas: studento vardo, pavardės, namų darbų rezultatų, egzamino rezultato.
2 parinktis - pusiau rankinis įvedimas: studento vardo, pavardės įvedimas, rezultatų generavimas.
3 parinktis - automatinis studentų vardų, pavardžių, rezultatų generavimas, jų apdorojimas ir išvedimas.
4 parinktis - skaitymas iš pasirinkto failo, rūšiavimas pasirinktinu būdu, duomenų apdorojimas ir išvedimas.
5 parinktis - studentų failų generavimas: studentų, namų darbų kiekio pasirinkimas ir išvedimas į studentų failą.
6 parinktis - programos nutraukimas.
```

Pasirinkus 1–4 parinktį, programa toliau klausia:

```
Rūšiavimo kriterijus  - pagal vardą, pavardę arba galutinį balą.
Skaičiavimo būdas     - galutinis balas skaičiuojamas vidurkiu arba mediana.
Išvedimo būdas        - į failą, į ekraną arba skirstymas į „nevykelių" ir „nerdų" failus.
```

---

## Kompiliavimas

Reikalavimai: CMake ≥ 3.10, MinGW (Windows) arba GCC (Linux).

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"   # Windows
# cmake ..                      # Linux
cmake --build . --target vector
```

Vietoje `vector` galima nurodyti `list` arba `deque`.

---

## Klasės ir Struct Kompiliavimo flag'ų testas

### 100 000 studentų
| Optimizavimas   | Versija  | Vykdymo laikas (ms) | Failo dydis (ms) |
|----------------:|---------:|--------------------:|-----------------:|
| O1     	  | struct   | 873.15              | 1035             |
|                 | class    | 657.62              | 1029             |
| O2     	  | struct   | 864.67              | 1036             |
|                 | class    | 653.08              | 1026             |
| O3     	  | struct   | 854.61              | 1055             |
|                 | class    | 641.19              | 1043             |

### 1 000 000 studentų
| Optimizavimas   | Versija  | Vykdymo laikas (ms) | Failo dydis (ms) |
|----------------:|---------:|--------------------:|-----------------:|
| O1     	  | struct   | 9623.41             | 1035             |
|                 | class    | 6617.74             | 1029             |
| O2     	  | struct   | 9543.10             | 1036             |
|                 | class    | 6474.63             | 1026             |
| O3     	  | struct   | 9424.76             | 1055             |
|                 | class    | 6518.39             | 1043             |

---

## Spartos tyrimas

Tyrimui naudojami prieš tai sugeneruoti failai. Bandyti visi rūšiavimo ir galutinio skaičiavimo būdai, rezultatai išreikšti vidurkiu.

**Specs:** AMD Ryzen 5 3600 · HyperX DDR4 16GB · SSD 970 M.2 250GB

---

### 1 strategija

Bendro studentai konteinerio skaidymas į du naujus to paties tipo konteinerius: „nevykeliai" ir „nerds". Tokiu būdu tas pats studentas yra dvejuose konteineriuose: bendrame studentai ir viename iš suskaidytų.

| Studentų kiekis | Konteineris | Nuskaitymas (ms) | Rūšiavimas (ms) | Skirstymas (ms) |
|----------------:|-------------|----------------:|----------------:|----------------:|
| 1 000           | vector      | 2.53            | 0.18            | 0.09            |
|                 | deque       | 1.74            | 0.21            | 0.08            |
|                 | list        | 2.07            | 0.09            | 0.11            |
| 10 000          | vector      | 45.12           | 26.47           | 0.43            |
|                 | deque       | 41.61           | 29.34           | 0.29            |
|                 | list        | 49.38           | 13.02           | 0.37            |
| 100 000         | vector      | 439.84          | 363.55          | 16.28           |
|                 | deque       | 441.07          | 404.92          | 15.83           |
|                 | list        | 451.29          | 171.84          | 24.51           |
| 1 000 000       | vector      | 4397.41         | 4868.73         | 192.74          |
|                 | deque       | 4418.56         | 5341.08         | 169.17          |
|                 | list        | 4454.83         | 2207.16         | 220.39          |
| 10 000 000      | vector      | 44284.6         | 62254.37        | 1880.62         |
|                 | deque       | 44514.8         | 69897.44        | 1865.93         |
|                 | list        | 44742.3         | 28843.91        | 2444.18         |

---

### 2 strategija

Bendro studentų konteinerio skaidymas panaudojant tik vieną naują konteinerį: „nevykeliai". Tokiu būdu, jei studentas yra nevykelis, jį turime įkelti į naująjį „nevykelių" konteinerį ir ištrinti iš bendro studentai konteinerio. Po šio žingsnio studentai konteineryje liks vien tik nerds.

| Studentų kiekis | Konteineris | Nuskaitymas (ms) | Rūšiavimas (ms) | Skirstymas (ms) |
|----------------:|-------------|----------------:|----------------:|----------------:|
| 1 000           | vector      | 4.67            | 2.00            | 0.36            |
|                 | deque       | 4.32            | 0.67            | 0.00            |
|                 | list        | 5.67            | 0.99            | 0.33            |
| 10 000          | vector      | 43.85           | 28.67           | 2.00            |
|                 | deque       | 49.99           | 29.15           | 0.00            |
|                 | list        | 45.86           | 14.33           | 0.99            |
| 100 000         | vector      | 427.02          | 377.19          | 12.96           |
|                 | deque       | 435.62          | 246.08          | 13.86           |
|                 | list        | 450.60          | 186.96          | 21.33           |
| 1 000 000       | vector      | 4294.58         | 5088.73         | 141.03          |
|                 | deque       | 4357.09         | 5189.21         | 161.02          |
|                 | list        | 4516.69         | 2378.67         | 259.93          |
| 10 000 000      | vector      | 45101.00        | 64604.73        | 1559.45         |
|                 | deque       | 42853.97        | 66047.37        | 1807.13         |
|                 | list        | 45069.80        | 30505.13        | 2956.44         |

---

### 3 strategija

Tas pats kaip 2 strategija, tačiau skirstymui naudojamas `std::partition` — elementai perstumiami vietoje (in-place) vienu perėjimu, po to nevykeliai nukopijuojami į naują konteinerį ir ištrinami iš bendro. Skirtingai nuo 2 strategijos, kuri naudoja `copy_if` ir `remove_if` (du perėjimai), `partition` tai atlieka vienu perėjimu.

| Studentų kiekis | Konteineris | Nuskaitymas (ms) | Rūšiavimas (ms) | Skirstymas (ms) |
|----------------:|-------------|----------------:|----------------:|----------------:|
| 1 000           | vector      | 2.57            | 0.53            | 0.00            |
|                 | deque       | 8.10            | 0.00            | 0.00            |
|                 | list        | 9.97            | 0.00            | 0.00            |
| 10 000          | vector      | 41.54           | 21.68           | 0.00            |
|                 | deque       | 43.23           | 20.37           | 0.00            |
|                 | list        | 45.32           | 16.32           | 0.00            |
| 100 000         | vector      | 444.37          | 280.55          | 3.97            |
|                 | deque       | 428.07          | 305.00          | 3.35            |
|                 | list        | 424.28          | 186.82          | 8.17            |
| 1 000 000       | vector      | 4453.88         | 3671.65         | 26.63           |
|                 | deque       | 4267.51         | 4031.19         | 65.79           |
|                 | list        | 4239.82         | 2598.73         | 100.15          |
| 10 000 000      | vector      | 44772.97        | 40601.10        | 234.93          |
|                 | deque       | 42661.50        | 48562.40        | 695.92          |
|                 | list        | 42550.20        | 33182.10        | 1073.19         |

---

## Išvados

Nuskaitymo ir rūšiavimo rezultatai išlieka panašūs visose trijose strategijose, kaip ir tikėtasi — skiriasi tik skirstymo dalis. Aiškiausiai tai matyti lyginant 2 ir 3 strategiją: `partition` (3 strat.) skirstymas yra žymiai greitesnis už `copy_if` + `remove_if` (2 strat.), nes atlieka tik vieną perėjimą per konteinerį vietoj dviejų. Skirtumas ypač ryškus didesniuose failuose — pvz., 10M studentų su vector: 2 strategija ~1559 ms, 3 strategija ~235 ms.

---

## Versijų istorija

| Versija | Pakeitimai |
|--------:|------------|
| v0.1 | Pradinis variantas. Duomenų įvedimas ranka, C masyvo ir `std::vector` realizacijos, galutinio balo skaičiavimas vidurkiu arba mediana, išvedimas į ekraną. |
| v0.2 | Pridėtas duomenų nuskaitymas iš failo, išvedimas į failą, rūšiavimas pagal vardą, pavardę arba galutinį balą. Projektas išskaidytas į kelis failus. |
| v0.3 | Funkcijos perkeltos į antraštinį (`.h`) ir realizacijos (`.cpp`) failus. Pridėtas klaidų gaudymas (`exception handling`). |
| v0.4 | Pridėtas failų generavimas, studentų skirstymas į „nevykelius" ir „nerdus", programos spartos tyrimas su 5 skirtingo dydžio failais. |
| v1.0 | Trys atskiros realizacijos (`vector`, `list`, `deque`). Išbandytos 3 skirstymo strategijos. Pridėtas `CMakeLists.txt`. |