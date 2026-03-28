#include <DX3D/All.h>

//NOTE: anything commented out is for memory leak detection in the game loop
//#define _CRTDBG_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

int main()
{
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		return EXIT_FAILURE;
	}

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	try 
	{
		dx3d::Game game({ {1280,720},dx3d::Logger::LogLevel::Info });
		game.run();
	}
	catch (const std::runtime_error&)
	{
		//_CrtDumpMemoryLeaks();
		return EXIT_FAILURE;
	}
	catch (const std::invalid_argument)
	{
		//_CrtDumpMemoryLeaks();
		return EXIT_FAILURE;
	}
	catch (const std::exception&)
	{
		//_CrtDumpMemoryLeaks();
		return EXIT_FAILURE;
	}
	catch (...)
	{
		//_CrtDumpMemoryLeaks();
		return EXIT_FAILURE;
	}
	
	CoUninitialize();

	//_CrtDumpMemoryLeaks();
	return EXIT_SUCCESS;
}