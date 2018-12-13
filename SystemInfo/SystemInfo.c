/**
 * @file SystemInfo.c
 * @author Erick Gonzalez Duran
 *
 * @date 10 Dec 2018
 *
 * El programa usa el estandar de documentacion que define el uso de
 * doxygen.
 * @see http://www.stack.nl/~dimitri/doxygen/manual/index.html
 *
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
// Revisamos si estamos en un sistema con Windows
#if defined(_WIN32) || defined(_WIN64)
//Si es asi, se realizan las siguientes acciones
#include <windows.h>
#define PLATAFORM_WINDOWS 1
#define PLATAFORM_LINUX 0
#define PLATAFORM_MAC 0
#define PLATAFORM_UNIX 0
//Si no, revisamos si estamos en un sistema con Linux
#elif defined(__linux__)
//Si es asi, se realizan las siguientes acciones
#include <linux/kernel.h>
#include <sys/sysinfo.h>
#define PLATAFORM_WINDOWS 0
#define PLATAFORM_LINUX 1
#define PLATAFORM_MAC 0
#define PLATAFORM_UNIX 0
//Si no, revisamos si estamos en un ordenador Mac
#elif defined(__APPLE__)
//Si es asi, se realizan las siguientes acciones
#include <unistd.h>
#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach_host.h>
#include <mach/vm_map.h>
#define PLATAFORM_WINDOWS 0
#define PLATAFORM_LINUX 0
#define PLATAFORM_MAC 1
#define PLATAFORM_UNIX 0
//Si no, revisamos si estamos en una sistema Unix
#elif defined(__unix__)
//Si es asi, se realizan las siguientes acciones
#include <unistd.h>
#include <sys/sysinfo.h>
#define PLATAFORM_WINDOWS 0
#define PLATAFORM_LINUX 0
#define PLATAFORM_MAC 0
#define PLATAFORM_UNIX 1

#endif

/**
 * Imprime en pantalla la informacion del sistema, solo en ordenadores que tengan un OS Windows (Version >= 7).
 */
void winSystem()
{
	long nprocs = -1;
    	long nprocs_max = -1;
	#ifdef _WIN32
	SYSTEM_INFO info;
	GetSystemInfo(&info);
  	printf("Hardware information: \n");  
   	printf("  OEM ID: %u\n", info.dwOemId);
   	printf("  Number of processors: %u\n", 
      		info.dwNumberOfProcessors); 
   	printf("  Processor type: %u\n", info.dwProcessorType); 
   	printf("  Minimum application address: %lx\n", 
      		info.lpMinimumApplicationAddress); 
   	printf("  Maximum application address: %lx\n", 
      		info.lpMaximumApplicationAddress); 
   	printf("  Active processor mask: %u\n", 
      		info.dwActiveProcessorMask); 
	#endif
	return;
}
	
/** 
 * Imprime en pantalla la informacion del sistema, solo en sistemas que tengan una Distribucion de Linux.
 */
void lnxSystem()
{
	#ifdef __linux__
 	const double megabyte = 1024 * 1024;
 	struct sysinfo si;
 	sysinfo (&si);
 	printf ("Total RAM   : %5.1f MB\n", si.totalram / megabyte);
 	printf ("Free RAM   : %5.1f MB\n", si.freeram / megabyte);
 	printf("Number of processors: %d\n", get_nprocs());
 	printf ("Process count : %d\n", si.procs);
 	#endif
	return;
}
	
/**
 * Imprime en pantalla la informacion del sistema, solo en equipos Mac
 */
void appSystem()
{
	//NOTA: Por el momento no contaba con ningun equipo Mac.
	#ifdef __APPLE__

	#endif
	return;
}

/**
 * Imprime en patanlla la informacion del sistema, solo en equipos con Unix.
 */
void unxSystem()
{	
	#ifdef __unix__
	const double megabyte = 1024 * 1024;
 	struct sysinfo si;
 	sysinfo (&si);
 	printf ("Total RAM   : %5.1f MB\n", si.totalram / megabyte);
 	printf ("Free RAM   : %5.1f MB\n", si.freeram / megabyte);
 	printf("Number of processors: %d\n", get_nprocs());
 	printf ("Process count : %d\n", si.procs);
	#endif
	return;
}

/** 
 * Funcion main, lo unico que hace es verificar los valores de los Macros de las diferentes plataformas.
 *@return 0
 */
int main()
{
	if (PLATAFORM_WINDOWS != 0)
	{
		winSystem();
	}
	else
	{
		if(PLATAFORM_LINUX != 0)
		{
			lnxSystem();
		}
		else
		{
			if(PLATAFORM_MAC != 0)
			{
				appSystem();
			}
			else
			{
				if(PLATAFORM_UNIX != 0)
				{
					unxSystem();
				}
				else
				{
					printf("SUPER ERROR");
				}
			}
		}
	}

	return 0;
}
