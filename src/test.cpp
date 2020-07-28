#include <memory>

#include "Application.h"

int main(int argc, char *argv[]){
	// Create application
	std::unique_ptr<Application> app = std::make_unique<Application>(800, 600, "GLFW Test");

	// Run application
	app->Run();

	// Exit Program
	return EXIT_SUCCESS;
}