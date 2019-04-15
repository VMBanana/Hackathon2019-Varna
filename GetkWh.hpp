#pragma once
/*
*	Get kilowatts per hour
*	Gets runtime of the ACs
*	It's broken :(
*/
void GetkWh() {
	chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
	while (AC[1].Running) {
		if (!AC[1].Running) break;
		chrono::steady_clock::time_point t2 = chrono::steady_clock::now();

		chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

		cout << "Runtime: " << time_span.count() << "seconds\n";
		this_thread::sleep_for(chrono::seconds(1));
	}
}