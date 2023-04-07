import matplotlib.pyplot as plt
import numpy as np
import os

ts = []
xs = []
us = []
Js = []

dim_x = 0
dim_u = 0

with open(os.path.dirname(__file__) + "/result/result.txt") as f:
    data = list(map(float, f.readline().split()))
    max_iter = int(data[0])
    dim_x = int(data[1])
    dim_u = int(data[2])

    ts = np.zeros(max_iter)
    xs = np.zeros((dim_x, max_iter))
    us = np.zeros((dim_u, max_iter))
    Js = np.zeros(max_iter)
    
    for i in range(max_iter):
        data = list(map(float, f.readline().split()))
        ts[i] = data[0]
        for j in range(dim_x):
            xs[j][i] = data[1 + j]
        for j in range(dim_u):
            us[j][i] = data[1 + dim_x + j]
        Js[i] = data[-1]

xs = np.array(xs)
us = np.array(us)
Js = np.array(Js)

fig = plt.figure(figsize=(14, 7.2))
ax_x = fig.add_subplot(2, 2, 1)
ax_u = fig.add_subplot(2, 2, 2)
ax_J = fig.add_subplot(2, 1, 2)

for i in range(dim_x):
    ax_x.plot(ts, xs[i], label=f"x({i})")

ax_x.set_xlabel("t [s]")
ax_x.set_ylabel("x")
ax_x.legend(loc="upper right")

for i in range(dim_u):
    ax_u.plot(ts, us[i], label=f"u({i})")

ax_u.set_xlabel("t [s]")
ax_u.set_ylabel("u")
ax_u.legend(loc="upper right")

ax_J.plot(ts, Js, label = "J")
ax_J.set_xlabel("t [s]")
ax_J.set_ylabel("J")
ax_J.legend(loc="upper right")


plt.tight_layout()
plt.savefig(os.path.dirname(__file__)+"/result/result.pdf")
plt.show()