Project Setup and Execution Guide:

Note: Ensure that your system is an Ubuntu 64-bit PC with administrative privileges (root access)


1. **Prepare your environment** by running the `install_libraries.sh` script.

    sh install_libraries.sh


2. Make sure your ICE Cast 2 server is ready with a mount point for Mp3 streaming. 
   If your ICE cast2 server is installed in the cloud environment make sure associated ports are open in the firewall settings.


3. **Navigate to the source code directory** where the project's Makefile is located. Run the following commands.

   make clean
   make


4. Modify configuration settings (if necessary) in the `config.xml` (located in source directory) file to suit your project requirements.

5. **Execute the project** by running the following command in the terminal:

   ./MainRTS
