# -*- coding: utf-8 -*-
"""
Title:"PHYS20161 Final Assignment in Doppler Spectroscopy."
This programme reads data and removes errors, bad data points and outliers. From the data
it calculates the minimum value of two parameters (angular frequency and initial velocity)
by performing aminimized chi-squared fit. The programme also calculates other observables
and a reduced chi-squared for the fit .Uncertainties are calculated for every result.
Student ID: 10521454
Author: Artemis Bouzaki
Created on Tue Nov 24 16:32:44 2020
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import fmin

#~~~~~~~~~~~~~~~~~~~~~~~~~~~Define constants~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SPEED_OF_LIGHT = 3.00E+08 # m/s
GRAVITATIONAL_CONSTANT = 6.67E-11 # m^3/kgs^2
MASS_OF_STAR = 5.53E+30 #kg
JOVIAN_MASS = 1.898E+27 #kg
ASTRONOMICAL_UNIT = 1.496E+11
LAMBDA_NAUGHT = 656.281 # nm
INITIAL_PHASE = np.pi # rad
OMEGA_START = 3.0E-8 # rad/s
INITIAL_VELOCITY_START = 50.0 # m/s

FILE_1 = 'doppler_data_1.csv'
FILE_2 = 'doppler_data_2.csv'

#~~~~~~~~~~~~~~~~~~~~~~~~~~~Open and validate files~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

def file_validation(file_1, file_2):
    """
    Checks if file is in directory.
    Returns:
        bool
    Raises:
        FileNotFoundError
    """
    try:
        open(file_1, file_2, 'r')
        file_1.close()
        file_2.close()
        return True
    except FileNotFoundError:
        return False

#~~~~~~~~~~~~~~~~~~~~~~~Remove outliers and errors from the data~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

def read_data(file_1, file_2):
    """
    Creates seperate arrays from columns of the original 2D array.
    Removes nan values and outliers.
    Parameters:
    file_1: string
    file_2: string
    Returns:
    time : array[floats].
    wavelengths : array[floats].
    wavelength_uncertainties : array[floats]
    """
    data_1 = np.genfromtxt(file_1, delimiter=','
                           , comments='%')
    data_2 = np.genfromtxt(file_2, delimiter=','
                           , comments='%')
    data_combined = np.concatenate((data_1, data_2))
    time = np.array([])
    wavelengths = np.array([])
    wavelength_uncertainties = np.array([])
    time = np.append(time, data_combined[:, :1])
    wavelengths = np.append(wavelengths, data_combined[:, 1:2])
    wavelength_uncertainties = np.append(wavelength_uncertainties, data_combined[:, 2:])
    x_variable = 0
    for i in wavelengths:
        if np.isnan(i):
            time = np.delete(time, x_variable)
            wavelengths = np.delete(wavelengths, x_variable)
            wavelength_uncertainties = np.delete(wavelength_uncertainties, x_variable)
            x_variable += 1
        else:
            x_variable += 1

    x_variable = 0
    for i in wavelengths:
        mean_value = np.mean(wavelengths)
        standard_deviation = np.std(wavelengths)
        if i >= mean_value + 5*standard_deviation or i <= mean_value - 5*standard_deviation:
            time = np.delete(time, x_variable)
            wavelengths = np.delete(wavelengths, x_variable)
            wavelength_uncertainties = np.delete(wavelength_uncertainties, x_variable)
            x_variable += 1
        else:
            x_variable += 1

    x_variable = 0
    for i in time:
        if np.isnan(i):
            time = np.delete(time, x_variable)
            wavelengths = np.delete(wavelengths, x_variable)
            wavelength_uncertainties = np.delete(wavelength_uncertainties, x_variable)
            x_variable += 1
        else:
            x_variable += 1
    x_variable = 0
    for i in wavelength_uncertainties:
        if i == 0 or np.isnan(i):
            time = np.delete(time, x_variable)
            wavelengths = np.delete(wavelengths, x_variable)
            wavelength_uncertainties = np.delete(wavelength_uncertainties, x_variable)
            x_variable += 1
        else:
            x_variable += 1
    return time, wavelengths, wavelength_uncertainties

TIME, WAVELENGTHS, WAVELENGTH_UNCERTAINTIES = read_data(FILE_1, FILE_2)

#~~~~~~~~~~~~~~~~~~~~~~Calculate important parameters~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

def time_in_seconds_calculation():
    """
    Converts time from years to seconds.
    Parameters:
    time : array[floats].
    Returns
   time_in_seconds: array[floats].
    """
    time_in_seconds = np.array([])
    for i in range(len(TIME)):
        time_in_seconds = np.append(time_in_seconds, TIME[i] * 31536.0E+3)
    return time_in_seconds

TIME_IN_SECONDS = time_in_seconds_calculation()

def line_of_sight_velocity_calculation():
    """
    Calculates the velocity at the line of sight for every wavelength
    and returns array of floats.
    Returns:
        LINE_OF_SIGHT_VELOCITY: array[floats]

    """
    line_of_sight_velocity = np.array([])
    for i in range(len(WAVELENGTHS)):
        line_of_sight_velocity = np.append(line_of_sight_velocity, SPEED_OF_LIGHT*
                                           ((WAVELENGTHS[i]/LAMBDA_NAUGHT) - 1))
    return line_of_sight_velocity

def errors_in_line_of_sight_velocity():
    """
    Returns array of the errors for the line of sight velocities.
    Returns:
    LINE_VELOCITY_ERRORS : array[floats]
    """
    line_velocity_errors = np.array([])
    for i in range(len(WAVELENGTH_UNCERTAINTIES)):
        line_velocity_errors = np.append(line_velocity_errors, SPEED_OF_LIGHT*
                                         ((WAVELENGTH_UNCERTAINTIES[i]/LAMBDA_NAUGHT)))
    return line_velocity_errors

LINE_VELOCITY_ERRORS = errors_in_line_of_sight_velocity()
LINE_OF_SIGHT_VELOCITY = line_of_sight_velocity_calculation()
#
def chi_squared_calculation(xy_values):
    """
    Creates arrays of values of omega and initial_velocity.
    Returns those values and the calculated chi-squared.
    Parameters:
    xy_values : array[floats]
    Returns:
    chi_squared: float.
    """
    omega_variable = xy_values[0]
    initial_velocity_variable = xy_values[1]
    chi_squared = np.sum(((initial_velocity_variable * np.sin(
        omega_variable*TIME_IN_SECONDS + INITIAL_PHASE) - LINE_OF_SIGHT_VELOCITY) / (
            LINE_VELOCITY_ERRORS)) ** 2)
    return chi_squared

#~~~~~~~~~~~~~~~~~~~~~~~~~~Perform initial fit using fmin~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

FIT_RESULTS = fmin(chi_squared_calculation, (OMEGA_START, INITIAL_VELOCITY_START),
                   full_output=True)

[OMEGA_MINIMUM, INITIAL_VELOCITY_MINIMUM] = FIT_RESULTS[0]
CHI_SQUARED_MINIMUM = FIT_RESULTS[1]

#~~~~~~~~~~~~~~~~~~~~~~~~Remove outliers after the first fit~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

OBSERVED_VERSUS_CALCULATED_VALUES = abs(LINE_OF_SIGHT_VELOCITY - INITIAL_VELOCITY_MINIMUM*
                                        np.sin(OMEGA_MINIMUM*TIME_IN_SECONDS
                                               + INITIAL_PHASE))
REMOVED_VALUES = np.where(OBSERVED_VERSUS_CALCULATED_VALUES > np.std(LINE_OF_SIGHT_VELOCITY))
LINE_OF_SIGHT_VELOCITY_CLEAN = np.delete(LINE_OF_SIGHT_VELOCITY, REMOVED_VALUES)
TIME_IN_SECONDS_CLEAN = np.delete(TIME_IN_SECONDS, REMOVED_VALUES)
WAVELENGTHS_CLEAN = np.delete(WAVELENGTHS, REMOVED_VALUES)
WAVELENGTH_UNCERTAINTIES_CLEAN = np.delete(WAVELENGTH_UNCERTAINTIES, REMOVED_VALUES)
LINE_VELOCITY_ERRORS_CLEAN = np.delete(LINE_VELOCITY_ERRORS, REMOVED_VALUES)

def second_chi_squared_calculation(xy_values):
    """
    Calculates the new value of chi-squared after the removal
    of bad data points.
    Parameters:
    time: array[floats]
    Returns:
    chi_squared_2: float.
    """
    omega_variable = xy_values[0]
    initial_velocity_variable = xy_values[1]
    chi_squared_2 = np.sum(((initial_velocity_variable * np.sin(
        omega_variable*TIME_IN_SECONDS_CLEAN + INITIAL_PHASE) - LINE_OF_SIGHT_VELOCITY_CLEAN) / (
            LINE_VELOCITY_ERRORS_CLEAN)) ** 2)
    return chi_squared_2

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Perform second fit using fmin~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

FIT_RESULTS_2 = fmin(second_chi_squared_calculation, (OMEGA_START, INITIAL_VELOCITY_START),
                     full_output=True)
[OMEGA_MINIMUM_2, INITIAL_VELOCITY_MINIMUM_2] = FIT_RESULTS_2[0]
CHI_SQUARED_MINIMUM_2 = FIT_RESULTS_2[1]

#~~~~~~~~~~~~~~~~~~~~~~~~~Plot velocity against time after removing bad data points~~~~~~~~~~~~~~~~~

TIME_SORTED = np.sort(TIME_IN_SECONDS_CLEAN)
VELOCITY_FIGURE = plt.figure(figsize=(6, 6), facecolor='skyblue'
                             , linewidth=3, edgecolor='midnightblue')
VELOCITY_FIT = VELOCITY_FIGURE.add_subplot(111)
for index in range(len(LINE_OF_SIGHT_VELOCITY_CLEAN)):
    VELOCITY_FIT.errorbar(TIME_IN_SECONDS_CLEAN[index], LINE_OF_SIGHT_VELOCITY_CLEAN[index],
                          yerr=LINE_VELOCITY_ERRORS_CLEAN[index], alpha=0.3,
                          color='darkblue')

VELOCITY_FIT.set_title(r'Line of sight velocity against time and line of best fit with '
                       '\n' r'$V_0$ = {0:.2f} m/s and $\omega$ = {1:.3f}E-8 rad/s'
                       .format(INITIAL_VELOCITY_MINIMUM_2, OMEGA_MINIMUM_2*1E+8),
                       fontsize=20, fontname='Times New Roman',
                       color='darkblue')
VELOCITY_FIT.set_xlabel('Time ($s$)', fontsize=14, color='darkblue')
VELOCITY_FIT.set_ylabel('Line of sight velocities (m $s^-1$)', fontsize=14,
                        color='darkblue')
VELOCITY_FIT.plot(TIME_SORTED, INITIAL_VELOCITY_MINIMUM_2*
                  np.sin(OMEGA_MINIMUM_2*TIME_SORTED+INITIAL_PHASE), color='blueviolet',
                  linewidth=2)
VELOCITY_FIT.scatter(TIME_IN_SECONDS_CLEAN, LINE_OF_SIGHT_VELOCITY_CLEAN,
                     alpha=0.7, color='darkcyan')
plt.savefig('Line velocity best fit.png', dpi=300)
plt.show()

#~~~~~~~~~~~~~~~~~~~~~~~~Plot function as contour plot~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

def mesh_arrays(initial_velocity_array, omega_array):
    """
    Returns two meshed arrays of size len(initial_velocity_array)
    by len(omega_array).
    Parameters:
    initial_velocity_array = array[floats].
    omega_array = array[floats].
    Returns:
    omega_array_mesh : array[floats].
    initial_velocity_array_mesh : array[floats].
    """
    initial_velocity_array_mesh = np.empty((0, len(initial_velocity_array)))
    for _ in range(len(omega_array)):
        initial_velocity_array_mesh = np.vstack((initial_velocity_array_mesh,
                                                 initial_velocity_array))
    omega_array_mesh = np.empty((0, len(omega_array)))
    for _ in range(len(initial_velocity_array)):
        omega_array_mesh = np.vstack((omega_array_mesh, omega_array))
    omega_array_mesh = np.transpose(omega_array_mesh)
    return initial_velocity_array_mesh, omega_array_mesh

def chi_squared_plot(initial_velocity_array, omega_array):
    """
    Returns chi-squared values as an array for different values of
    frequency and initial velocity.
    Parameters:
    initial_velocity_array : array[floats].
    omega_array : array[floats].
    Returns:
    chi_squared_value : array[floats].
    """
    chi_squared_value = 0
    for i in range(len((TIME_IN_SECONDS_CLEAN))):
        chi_squared_array = (((initial_velocity_array*np.sin(omega_array*TIME_IN_SECONDS_CLEAN[i]
                                                             + INITIAL_PHASE))
                              -LINE_OF_SIGHT_VELOCITY_CLEAN[i])
                             /LINE_VELOCITY_ERRORS_CLEAN[i])**2
        chi_squared_value += chi_squared_array
    return chi_squared_value

INITIAL_VELOCITY_VALUES = np.linspace(INITIAL_VELOCITY_MINIMUM_2 * 0.95,
                                      INITIAL_VELOCITY_MINIMUM_2 * 1.05,
                                      len(LINE_OF_SIGHT_VELOCITY_CLEAN))
OMEGA_VALUES = np.linspace(OMEGA_MINIMUM_2 * 0.95, OMEGA_MINIMUM * 1.05,
                           len(LINE_OF_SIGHT_VELOCITY_CLEAN))
INITIAL_VELOCITY_MESH, OMEGA_MESH = mesh_arrays(INITIAL_VELOCITY_VALUES, OMEGA_VALUES)
PARAMETERS_CONTOUR_PLOT = plt.figure(figsize=(6, 6), facecolor='cornsilk'
                                     , linewidth=3, edgecolor='darkred')
AXES = PARAMETERS_CONTOUR_PLOT.add_subplot(111)
AXES.set_title(r'$\chi^2$ plotted against parameters.', fontsize=16,
               fontname='Times New Roman', color='purple')
AXES.set_xlabel(r'$V_0$ (m $s^-1$)', fontsize=14, color='purple')
AXES.set_ylabel(r'$\omega$ (rad $s^-1$)', fontsize=14, color='purple')
CONTOUR_2D = AXES.contour(INITIAL_VELOCITY_MESH, OMEGA_MESH, chi_squared_plot(
    INITIAL_VELOCITY_MESH, OMEGA_MESH), 10)
FILLED_CONTOUR_2D = AXES.contourf(INITIAL_VELOCITY_MESH, OMEGA_MESH, chi_squared_plot(
    INITIAL_VELOCITY_MESH, OMEGA_MESH), 10)

PARAMETERS_CONTOUR_PLOT.colorbar(FILLED_CONTOUR_2D)
AXES.scatter(INITIAL_VELOCITY_MINIMUM_2, OMEGA_MINIMUM_2,
             color='r', label=r'Minimum point at $\chi^2$ = 62.85')
AXES.clabel(CONTOUR_2D, inline=1, fontsize=12, colors='w')
plt.legend()
plt.savefig('Parameters contour plot.png', dpi=300)
plt.show(PARAMETERS_CONTOUR_PLOT)

#~~~~~~~~~~~~~~~~~~~~~~~~~~Calculate uncertainties in parameters~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

def errors_in_parameters():
    """
    Calculates errors in omega and initial velocity by extracting the
    minimum and maximum values of the arrays that give chi-minimum+1.
    Returns:
    initial_velocity_errors: float
    omega_errors: float
    """
    chi_squared_array = chi_squared_plot(INITIAL_VELOCITY_MESH, OMEGA_MESH)
    initial_velocity_errors = np.array([])
    omega_errors = np.array([])
    for i in range(len(chi_squared_array[0])):
        x_variable = 0
        while x_variable < len(chi_squared_array):
            if (1.00009*(CHI_SQUARED_MINIMUM_2 + 1) > chi_squared_array[i, x_variable] and (
                    0.99998*(CHI_SQUARED_MINIMUM_2 + 1) < chi_squared_array[i, x_variable])):
                initial_velocity_errors = np.append(initial_velocity_errors,
                                                    INITIAL_VELOCITY_MESH[i, x_variable])
                omega_errors = np.append(omega_errors, OMEGA_MESH[i, x_variable])
                x_variable += 1
            else:
                x_variable += 1

    initial_velocity_errors = (np.max(initial_velocity_errors)- np.min(initial_velocity_errors))/2
    omega_errors = (np.max(omega_errors)- np.min(omega_errors))/2
    return initial_velocity_errors, omega_errors

INITIAL_VELOCITY_ERROR, OMEGA_ERROR = errors_in_parameters()

#~~~~~~~~~~~~~~~~~~~~~~~~~Calculate reduced chi-squared and results~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

def reduced_chi_squared_calculation():
    """
    Calculates the reduced chi-squared from the minimum chi-squared.
    Returns:
    reduced_chi_squared : float
    """
    reduced_chi_squared = CHI_SQUARED_MINIMUM_2 / (len(TIME_IN_SECONDS_CLEAN)-2)
    return reduced_chi_squared

def distance_from_star_calculation():
    """
    Calculates and returns the distance between the planet and the star (in
    m) along with its uncertainty using the calculated minimum value of omega.
    Returns:
    distance_from_star: float
    distance_uncertainty: float
    """
    orbital_period = 2 * np.pi / OMEGA_MINIMUM_2
    orbital_period_uncertainty = 2* np.pi*OMEGA_ERROR*orbital_period/OMEGA_MINIMUM_2
    distance_from_star = np.cbrt(GRAVITATIONAL_CONSTANT * MASS_OF_STAR * orbital_period**2
                                 /(4* np.pi**2))
    distance_uncertainty = (2/3)*orbital_period_uncertainty*(
        np.cbrt(GRAVITATIONAL_CONSTANT * MASS_OF_STAR/(4*orbital_period*np.pi**2)))
    return distance_from_star, distance_uncertainty

def planet_velocity_calculation(distance_from_star, distance_uncertainty):
    """
    Calculates and returns the orbital velocity of the planet in m/s along
    with its uncertainty.
    Parameters:
    distance_from_star : float
    distance_uncertainty : float
    Returns:
    planet_velocity : float
    planet_velocity_uncertainty: float
    """
    planet_velocity = np.sqrt(GRAVITATIONAL_CONSTANT * MASS_OF_STAR / distance_from_star)
    planet_velocity_uncertainty = (1/2) *distance_uncertainty*(
        np.sqrt(GRAVITATIONAL_CONSTANT * MASS_OF_STAR / (distance_from_star**3)))
    return planet_velocity, planet_velocity_uncertainty

def mass_of_planet_calculation(planet_velocity, planet_velocity_uncertainty):
    """
    Calculates and returns the mass of the planet in kg along with its
    uncertainty.
    Parameters:
    planet_velocity : float
    planet_velocity_uncertainty: float
    Returns:
    mass_of_planet : float
    mass_uncertainty
    """
    mass_of_planet = (MASS_OF_STAR * INITIAL_VELOCITY_MINIMUM_2) / planet_velocity
    mass_uncertainty = mass_of_planet*np.sqrt(
        (INITIAL_VELOCITY_ERROR/INITIAL_VELOCITY_MINIMUM_2)**2
        +(planet_velocity_uncertainty/planet_velocity)**2)
    return mass_of_planet, mass_uncertainty

DISTANCE_FROM_STAR, DISTANCE_UNCERTAINTY = distance_from_star_calculation()
PLANET_VELOCITY, PLANET_VELOCITY_UNCERTAINTY = planet_velocity_calculation(DISTANCE_FROM_STAR,
                                                                           DISTANCE_UNCERTAINTY)
MASS_OF_PLANET, MASS_UNCERTAINTY = mass_of_planet_calculation(PLANET_VELOCITY,
                                                              PLANET_VELOCITY_UNCERTAINTY)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~Print final results~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

print('The minimum value of angular frequency is ({0: .3f} \u00B1 {1: .3f})E-8 rad/s.'.
      format(OMEGA_MINIMUM_2*1.0E+8, OMEGA_ERROR*1.0E+8))
print('The minimum value of the initial velocity is {0: .2f} \u00B1 {1: .2f} m/s.'.
      format(INITIAL_VELOCITY_MINIMUM_2, INITIAL_VELOCITY_ERROR))
print('The distance from the planet to the star is {0: .3f} \u00B1 {1: .3f} AU.'.
      format(DISTANCE_FROM_STAR/ASTRONOMICAL_UNIT, DISTANCE_UNCERTAINTY/ASTRONOMICAL_UNIT))
print('The mass of the planet is {0: .3f} \u00B1 {1: .3f} Jovian masses.'.
      format(MASS_OF_PLANET/JOVIAN_MASS, MASS_UNCERTAINTY/JOVIAN_MASS))
print('The reduced chi-squared is {0: .3f}.'.
      format(reduced_chi_squared_calculation()))
