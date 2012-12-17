#include "ring_buffer.h"

int main() {
	std::cout << "\nWrite more values than size of buffer: ignore" << std::endl;
	std::cout << "---------------------------------------------";

	RingBuffer<int> buffer1(4);

	buffer1.write(1);
	buffer1.write(2);
	buffer1.write(3);
	buffer1.write(4);
	buffer1.write(5);
	buffer1.write(6);

	buffer1.print();

	buffer1.read();
	buffer1.read();
	buffer1.read();


	std::cout << "\nWrite more values than size of buffer: throw exception" << std::endl;
	std::cout << "------------------------------------------------------";

	try {
		RingBuffer<int, BufferOverflowExceptionPolicy> buffer2(4);

		buffer2.write(1);
		buffer2.write(2);
		buffer2.write(3);
		buffer2.write(4);
		buffer2.write(5);
		buffer2.write(6);
	} catch(BufferOverflowExceptionPolicy<int>::Exception &exception) {
		std::cout << exception.what() << std::endl;
	}


	std::cout << "\nWrite more values than size of buffer: overwrite" << std::endl;
	std::cout << "------------------------------------------------";

	RingBuffer<int, BufferOverflowOverwritePolicy> buffer3(4);

	buffer3.write(1);
	buffer3.write(2);
	buffer3.write(3);
	buffer3.write(4);
	buffer3.write(5);
	buffer3.write(6);

	buffer3.print();

	buffer3.read();
	buffer3.read();
	buffer3.read();


	std::cout << "\nRead from empty Buffer: throw exception" << std::endl;
	std::cout << "---------------------------------------";

	try {
		RingBuffer<double, BufferOverflowOverwritePolicy, EmptyBufferExceptionPolicy> buffer4(4);

		buffer4.read();
	} catch(EmptyBufferExceptionPolicy<double>::Exception &exception) {
		std::cout << exception.what() << std::endl;
	}


	std::cout << "\nRead from empty Buffer: return default" << std::endl;
	std::cout << "--------------------------------------" << std::endl;

	RingBuffer<double> buffer5(4);
	buffer5.read();

	return 0;
}