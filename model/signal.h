#include <stdint.h>
#include <stdbool.h>
#include <complex.h>

#ifndef __GUARD_SIGNAL_H
#define __GUARD_SIGNAL_H

/* Signal metadata struct */
typedef struct {
    double start_time;
    double sampling_frequency;
    uint64_t num_samples;
} signal_info_t;

typedef struct {
    signal_info_t info;
    double* pValues;
} real_signal_t;

typedef struct {
    signal_info_t info;
    double complex* pValues;
} complex_signal_t;

typedef struct {
    union {
        real_signal_t real_signal;
        complex_signal_t complex_signal;
    };
    bool treat_as_complex;
    bool is_inherently_complex;
} signal_t;

void signal_free_values(signal_t* pSignal);
void real_signal_free_values(real_signal_t* pSignal);
void complex_signal_free_values(complex_signal_t* pSignal);

void signal_alloc_values(signal_t* pSignal);
void real_signal_alloc_values(real_signal_t* pSignal);
void complex_signal_alloc_values(complex_signal_t* pSignal);

void signal_copy_values(signal_t* pDestination, signal_t* pSource);
void real_copy_values(real_signal_t* pDestination, real_signal_t* pSource);
void complex_signal_copy_values(complex_signal_t* pDestination, complex_signal_t* pSource);
void* signal_get_values(signal_t* pSignal);
double* real_signal_get_values(real_signal_t* pSignal);
double complex* complex_signal_get_values(complex_signal_t* pSignal);
void signal_set_num_samples(signal_t* pSignal, uint64_t numSamples);
uint64_t signal_get_num_samples(signal_t* pSignal);
void signal_set_sampling_frequency(signal_t* pSignal, double samplingFrequency);
double signal_get_sampling_frequency(signal_t* pSignal);
void signal_set_start_time(signal_t* pSignal, double startTime);
double signal_get_start_time(signal_t* pSignal);

void signal_domain_adjust_start_time(signal_t* pSignal, double newStartTime);
void signal_domain_adjust_end_time(signal_t* pSignal, double oldEndTime, double newEndTime);
void real_signal_domain_adjust_start_time(real_signal_t* pSignal, double newStartTime);
void real_signal_domain_adjust_end_time(real_signal_t* pSignal, double oldEndTime, double newEndTime);
void complex_signal_domain_adjust_start_time(complex_signal_t* pSignal, double newStartTime);
void complex_signal_domain_adjust_end_time(complex_signal_t* pSignal, double oldEndTime, double newEndTime);

void signal_reverse(signal_t* pSignal);
void real_signal_reverse(real_signal_t* pSignal);
void complex_signal_reverse(complex_signal_t* pSignal);

void signal_timeshift(signal_t* pSignal, double timeshiftValue);
void signal_collapse_signals_tdomains(signal_t* pSignal_1, signal_t* pSignal_2);
void real_signal_timeshift(real_signal_t* pSignal, double timeshiftValue);
void real_signal_collapse_signals_tdomains(real_signal_t* pSignal_1, real_signal_t* pSignal_2);
void complex_signal_timeshift(complex_signal_t* pSignal, double timeshiftValue);
void complex_signal_collapse_signals_tdomains(complex_signal_t* pSignal_1, complex_signal_t* pSignal_2);

/**
 * @param pSignal_in Input signal
 * @param pSignalRe_out Address where to store the real part signal obtained from the input signal
 * @param pSignalIm_out Address where to store the imaginary part signal obtained from the input signal
 */
void complex_signal_extract_cartesian(complex_signal_t* pSignal_in, real_signal_t* pSignalRe_out, real_signal_t* pSignalIm_out);
/**
 * @param pSignal_in Input signal
 * @param pSignalCmag_out Address where to store the complex magnitude signal obtained from the input signal
 * @param pSignalCarg_out Address where to store the complex argument signal obtained from the input signal     
 */
void complex_signal_extract_polar(complex_signal_t* pSignal_in, real_signal_t* pSignalCmag_out, real_signal_t* pSignalCarg_out);

/**
 * @brief Converts a real signal to a complex signal using a target signal pointer as destination
 * @details The imaginary part of the complex signal is set to zero while the real part of the signal is preserved from the input signal
 * @param pSignal_in Input signal
 * @param pSignal_out Address where to store the complex signal obtained from the input signal
 */
void real_signal_to_complex(real_signal_t* pSignal_in, complex_signal_t* pSignal_out);

/**
 * @brief Turn a provided signal into a complex signal
 */
void signal_complexize(signal_t* pSignal);

/**
 * @brief Converts a complex signal to a real signal using a target signal pointer as destination
 * @details The real part of the complex signal is preserved from the input signal while the imaginary part is discarded
 * @param pSignal_in Input signal
 * @param pSignal_out Address where to store the real signal obtained from the input signal
 */
void complex_signal_to_real(complex_signal_t* pSignal_in, real_signal_t* pSignal_out);

/**
 * @brief Turn a provided signal into a real signal by discarding the imaginary part
 */
void signal_realize(signal_t* pSignal);
#endif // __GUARD_SIGNAL_H