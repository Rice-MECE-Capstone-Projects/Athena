# Test your Sifive board in Freedom studio

1. Create a new project:
a. In Freedom Studio, go to 'File > New > Freedom E SDK Project'.
b. Give your project a name and select the proper 'Target Hardware' based on your SiFive board.
c. Select an example program or create your own.
d. Click 'Finish' to create the project.
    
    ![截屏2023-04-21 下午9.40.58.png](Test%20your%20Sifive%20board%20in%20Freedom%20studio%20ab9b750666ac4ee9a32e072d9c85b253/%25E6%2588%25AA%25E5%25B1%258F2023-04-21_%25E4%25B8%258B%25E5%258D%25889.40.58.png)
    
2. Build the project:
a. Choose the correct board. (Here is sifive-hifive-revb)
b. Select 'openOCD'.
c. Click 'Finish' to build the project.

![截屏2023-04-21 下午11.29.19.png](Test%20your%20Sifive%20board%20in%20Freedom%20studio%20ab9b750666ac4ee9a32e072d9c85b253/%25E6%2588%25AA%25E5%25B1%258F2023-04-21_%25E4%25B8%258B%25E5%258D%258811.29.19.png)

1. Debug the project:
a. In the 'Project Explorer' view, right-click on your project and select 'Debug As > Debug Configurations'.
b. Create a new debug configuration under 'GDB SEGGER J-Link Debugging' or 'GDB OpenOCD Debugging', depending on your JTAG adapter.
c. In the 'Main' tab, set the 'Project' field to your project's name and the 'C/C++ Application' field to the path of the generated ELF file (e.g., 'Debug/your_project_name.elf').
d. In the 'Debugger' tab, configure the settings according to your JTAG adapter (e.g., the device name, interface, and speed).
e. Click 'Apply', then 'Debug' to start debugging. This will load the program onto your SiFive RevB board and start a debug session.
    
    ![截屏2023-04-21 下午11.35.08.png](Test%20your%20Sifive%20board%20in%20Freedom%20studio%20ab9b750666ac4ee9a32e072d9c85b253/%25E6%2588%25AA%25E5%25B1%258F2023-04-21_%25E4%25B8%258B%25E5%258D%258811.35.08.png)
    
2. Run the code on your SiFive RevB board:
a. In the 'Debug' perspective, click the 'Resume' button or press F8 to start executing the code on your board.
b. Observe the results on your board or through a connected serial terminal if required.
c. Use the 'Pause', 'Step Over', 'Step Into', and 'Step Return' buttons to control the execution and debug your code.
    
    ![截屏2023-04-21 下午11.45.53.png](Test%20your%20Sifive%20board%20in%20Freedom%20studio%20ab9b750666ac4ee9a32e072d9c85b253/%25E6%2588%25AA%25E5%25B1%258F2023-04-21_%25E4%25B8%258B%25E5%258D%258811.45.53.png)
    
3. Terminate the debug session:
a. When you are done debugging, click the 'Terminate' button or press Ctrl+F2 to end the debug session.
4. Click reset botton and you can see information through serial port.

![截屏2023-04-21 下午11.53.05.png](Test%20your%20Sifive%20board%20in%20Freedom%20studio%20ab9b750666ac4ee9a32e072d9c85b253/%25E6%2588%25AA%25E5%25B1%258F2023-04-21_%25E4%25B8%258B%25E5%258D%258811.53.05.png)