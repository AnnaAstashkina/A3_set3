import matplotlib.pyplot as plt

array_sizes = [
    500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400,
    2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900, 4000, 4100, 4200, 4300,
    4400, 4500, 4600, 4700, 4800, 4900, 5000, 5100, 5200, 5300, 5400, 5500, 5600, 5700, 5800, 5900, 6000, 6100, 6200,
    6300, 6400, 6500, 6600, 6700, 6800, 6900, 7000, 7100, 7200, 7300, 7400, 7500, 7600, 7700, 7800, 7900, 8000, 8100,
    8200, 8300, 8400, 8500, 8600, 8700, 8800, 8900, 9000, 9100, 9200, 9300, 9400, 9500, 9600, 9700, 9800, 9900, 10000
]

quick_sort_times_near = [
    3.2, 4.84, 4.968, 5.9936, 6.79872, 7.55974, 8.51195, 9.50239, 10.1005, 11.0201, 12.004, 14.0008, 14.4002, 14.88,
    16.776, 17.9552, 18.591, 23.9182, 30.9836, 22.5967, 21.1193, 24.2239, 24.6448, 25.329, 24.6658, 24.9332, 25.9866,
    27.7973, 27.7595, 28.7519, 28.9504, 29.7901, 32.158, 32.0316, 33.2063, 34.0413, 36.2083, 35.8417, 37.9683, 39.7937,
    40.7587, 42.1517, 41.4303, 41.2861, 43.8572, 56.3714, 50.2743, 48.2549, 47.451, 46.4902, 58.898, 58.9796, 69.7959,
    53.3592, 50.2718, 51.4544, 51.8909, 66.7782, 57.7556, 55.5511, 57.5102, 57.902, 57.3804, 58.6761, 59.3352, 59.667,
    61.1334, 62.2267, 63.4453, 62.8891, 66.5778, 68.5156, 66.3031, 67.8606, 66.9721, 68.5944, 68.7189, 69.9438, 75.5888,
    73.7178, 73.3436, 73.4687, 73.8937, 83.5787, 79.9157, 79.9831, 139.597, 93.5193, 88.1039, 87.2208, 91.0442, 95.2088,
    90.6418, 95.3284, 87.8657, 92.3731
]

intro_sort_times_near = [
    7.41842e-309, 1.48368e-309, 2.96737e-310, 0.4, 1.08, 1.216, 1.2432, 1.24864, 1.24973, 1.44995, 1.28999, 2.258,
    2.2516, 2.45032, 2.89006, 2.57801, 3.1156, 4.02312, 4.60462, 3.92092, 3.78418, 4.15684, 4.23137, 3.84627, 3.76925,
    3.95385, 4.39077, 4.87815, 4.97563, 4.99513, 5.19903, 5.03981, 5.20796, 5.64159, 5.92832, 6.78566, 6.55713, 6.31143,
    6.26229, 7.25246, 6.85049, 6.5701, 7.31402, 7.4628, 7.69256, 8.33851, 9.0677, 8.61354, 8.72271, 7.94454, 10.9889,
    10.1978, 11.8396, 9.36791, 8.87358, 8.97472, 9.59494, 9.91899, 9.9838, 10.1968, 10.0394, 12.0079, 10.4016, 10.6803,
    10.9361, 10.7872, 11.1574, 11.4315, 11.8863, 11.3773, 14.0755, 13.2151, 12.243, 12.2486, 12.8497, 12.7699, 12.754,
    12.7508, 13.7502, 13.35, 13.07, 13.814, 13.9628, 16.7926, 14.7585, 15.1517, 26.2303, 17.0461, 15.4092, 16.0818,
    17.0164, 17.2033, 17.2407, 19.2481, 16.8496, 17.5699
]

plt.figure(figsize=(12, 6))

plt.plot(array_sizes, quick_sort_times_near, label='QuickSort', color='blue', marker='o')
plt.plot(array_sizes, intro_sort_times_near, label='IntroSort', color='orange',
         marker='o')

plt.title(
    'Сравнение QuickSort и IntroSort на почти отсортированном массиве')
plt.xlabel('Длина массива')
plt.ylabel('Время выполнения (мс)')
plt.legend()
plt.grid()
plt.xscale('linear')
plt.yscale('linear')
plt.tight_layout()

plt.show()
