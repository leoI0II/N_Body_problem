all: pro

pro: coords.o barycenter_zeroing.o barycenter_velocity.o barycenter.o systems_energy.o angular_momentum.o grav_func.o n_body.o kepler.o solver_rk4.o solver_3div8_4order.o solver_Adams_Bashforth.o
	g++ -g n_body.o coords.o barycenter_zeroing.o barycenter_velocity.o barycenter.o systems_energy.o angular_momentum.o grav_func.o kepler.o solver_rk4.o solver_3div8_4order.o solver_Adams_Bashforth.o -o app

n_body.o:
	g++ -c -g n_body.cpp
barycenter.o:
	g++ -c -g barycenter.cpp
barycenter_velocity.o:
	g++ -c -g barycenter_velocity.cpp
barycenter_zeroing.o:
	g++ -c -g barycenter_zeroing.cpp
#log.o:
#	g++ -c log.cpp
coords.o:
	g++ -c -g coords.cpp
angular_momentum.o:
	g++ -c -g angular_momentum.cpp
systems_energy.o:
	g++ -c -g systems_energy.cpp
grav_func.o:
	g++ -c -g grav_func.cpp
solver_rk4.o:
	g++ -c -g solver_rk4.cpp
solver_3div8_4order.o:
	g++ -c -g solver_3div8_4order.cpp
solver_Adams_Bashforth.o:
	g++ -c -g solver_Adams_Bashforth.cpp
kepler.o:
	g++ -c -g kepler.cpp
clean:
	rm *.o
