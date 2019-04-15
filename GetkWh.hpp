#pragma once
#include <chrono>
/*
*	Get kilowatts per hour
*	Gets runtime of the ACs
*/
void GetkWh() {
	chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
	while (true) {
		if (AC[0].Running) {
			chrono::steady_clock::time_point t2 = chrono::steady_clock::now() + chrono::seconds(1);

			chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
			El.TotalRuntime += trunc(time_span.count());
			cout << "Runtime AC[0]: " << time_span.count() << "seconds\n";
		}
		else t1 = chrono::steady_clock::now();

		if (AC[1].Running) {
			chrono::steady_clock::time_point t2 = chrono::steady_clock::now() + chrono::seconds(1);

			chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

			El.TotalRuntime += trunc(time_span.count());
			cout << "Runtime AC[1]: " << time_span.count() << "seconds\n";
		}
		else t1 = chrono::steady_clock::now();

		this_thread::sleep_for(chrono::seconds(1));
	}
}