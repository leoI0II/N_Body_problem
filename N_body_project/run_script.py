import subprocess, sys
import matplotlib.pyplot as plt
# from numpy import float128 as fl

if len(sys.argv) < 2:
    print(f"You have to enter program options. Check help info printed 'python3 ./{sys.argv[0]} help'.")
    sys.exit()
    
if sys.argv[1] == 'help':
    print("Use: run_script.py [(RECOMPILE)yes/no] [NUMERICAL_METHOD] [T=NUM](period) [h=NUM](time step) [PLANET_NAME]...")
    print("First argument needed for recompilation: yes or no.")
    print("Second argument have to be a numerical method: RK4, 3div8 or AB4.")
    print("Third argument is period time, ex: T=100000.")
    print("Fourth argument is time step, ex: h=100.")
    print("Last arguments are planets, ex: sun earth moon.")
    print("Available list of bodies:")
    print("\tearth\n\tsun\n\tmoon\n\tmercury\n\tjupiter\n\tsaturn\n\tmars")
    sys.exit()

rec = False

if sys.argv[1] in ['yes', 'no']:
    if sys.argv[1] == 'yes':
        rec = True
else:
    print("Need info about recompile set. Check help info.")
    sys.exit()

num_method = ["RK4", "3div8", "AB4"];
if sys.argv[2] not in num_method:
    print("You have to insert a numerical method. Check help info.")
    sys.exit()
    
time_num1 = sys.argv[3][2:]
time_num2 = sys.argv[4][2:]
try:
    num1 = int(time_num1)
    num2 = int(time_num2)
except ValueError:
    print("You have to enter a integer value for TIME period and h step time! Check help info.")
    sys.exit()

bodies = ['earth', 'sun', 'moon', 'mercury', 'jupiter', 'saturn', 'mars']
for i in range(5, len(sys.argv)):
    if sys.argv[i] not in bodies:
        print("You have to enter bodies from available list. Check help info.")
        sys.exit()

if rec == True:
    make = subprocess.run("make".split(), stdout=True)
    print(make)
    print("Error:", make.check_returncode())
    cl = subprocess.run("make clean".split(), stdout=True)
    print(cl)
    print("Error:", cl.check_returncode())

run_command = ["./app"]
for i in range(2, len(sys.argv)):
    run_command.append(sys.argv[i])
    
run_program = subprocess.run(run_command, stdout=True)
# print("Program code output:", subprocess.run(run_command, stdout=True).check_returncode())
print(run_program)
print("Error:", run_program.check_returncode())



kep = [[], []]

bodies_files = []
for i in range(5, len(sys.argv)):
    bodies_files.append(open(sys.argv[i] + '.txt'))
    
bodies_dats = [ [[], []] for _ in range(len(bodies_files))]

for file in range(len(bodies_files)):
    for row in bodies_files[file]:
        row = row.split(", ")
        bodies_dats[file][0].append(float(row[0]))
        bodies_dats[file][1].append(float(row[1]))
        
for file in bodies_files:
    file.close()

dats_inv = [[], [], [], [], []]
inv = open('inv.txt'); i = 0

if len(bodies_files) == 2:
    dats_inv = [[], [], [], [], [], []]
    for row in inv:
        if i == 0:
            i += 1
            continue
        row = row.split(' ')
        for i in range(len(row)):
            dats_inv[i].append(float(row[i]))
else:
    for row in inv:
        if i == 0:
            i += 1
            continue
        row = row.split(' ')
        for i in range(len(row)):
            if row[i] == '\n':
                continue
            dats_inv[i].append(float(row[i]))
inv.close()

inv_filename_png = f'inv_{sys.argv[2]}_{sys.argv[3]}_{sys.argv[4]}'
bodies_filename_png = f'orbital_plot_{sys.argv[2]}_{sys.argv[3]}_{sys.argv[4]}'
for i in range(5, len(sys.argv)):
    inv_filename_png += f'_{sys.argv[i]}'
    bodies_filename_png += f'_{sys.argv[i]}'
inv_filename_png += '.png'
bodies_filename_png += '.png'

l = len(bodies_dats)
c = len(bodies_dats[0][0])

plt.figure(figsize=(15, 10))
plt.title(f'Method: {sys.argv[2]}, {sys.argv[3]}, {sys.argv[4]}.')
for i in range(len(bodies_dats)):
    plt.plot(bodies_dats[i][0], bodies_dats[i][1], linewidth=2, label=sys.argv[i+5])
    
for i in range(l):
    plt.plot([bodies_dats[i][0][c-1]], [bodies_dats[i][1][c-1]], marker='o', markersize=10)

if (len(bodies_dats) == 2):
    kepler = open('kepler.txt')
    for row in kepler:
        row = row.split(', ')
        kep[0].append(float(row[0]))
        kep[1].append(float(row[1]))

    kepler.close()
    plt.plot(kep[0], kep[1], label='kepler')
    plt.plot([kep[0][len(kep[0])-1]], [kep[1][len(kep[1])-1]], marker='*', markersize=10)
    
plt.legend()
plt.savefig(bodies_filename_png)
plt.show()


plt.figure(figsize=(15, 10))
plt.subplot(321)
plt.plot(dats_inv[0], dats_inv[1])
plt.title('BarRvec')
plt.subplot(322)
plt.plot(dats_inv[0], dats_inv[2])
plt.title('BarRvel')
# plt.subplot(323)
# plt.plot(dats_inv[0], dats_inv[3])
# plt.title('BarVel')
plt.subplot(323)
plt.plot(dats_inv[0], dats_inv[3])
plt.title('AngMom')
plt.subplot(324)
plt.plot(dats_inv[0], dats_inv[4])
plt.title('TotEnergy')

if len(bodies_dats) == 2:
    plt.subplot(325)
    plt.plot(dats_inv[0], dats_inv[5])
    plt.title('delta(t)')

plt.savefig(inv_filename_png)
plt.show()
