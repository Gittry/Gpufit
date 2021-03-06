#include "cpufit.h"
#include "../Gpufit/constants.h"
#include "interface.h"

#include <string>

std::string last_error ;

int cpufit
(
    size_t n_fits,
    size_t n_points,
    float * data,
    float * weights,
    int model_id,
    float * initial_parameters,
    float tolerance,
    int max_n_iterations,
    int * parameters_to_fit,
    int estimator_id,
    size_t user_info_size,
    char * user_info,
    float * output_parameters,
    int * output_states,
    float * output_chi_squares,
    int * output_n_iterations
)
try
{
    __int32 n_points_32 = 0;
    if (n_points <= (unsigned int)(std::numeric_limits<__int32>::max()))
    {
        n_points_32 = __int32(n_points);
    }
    else
    {
        throw std::runtime_error("maximum number of data points per fit exceeded");
    }

    FitInterface fi(
        data,
        weights,
        n_fits,
        n_points_32,
        tolerance,
        max_n_iterations,
        static_cast<EstimatorID>(estimator_id),
        initial_parameters,
        parameters_to_fit,
        user_info,
        user_info_size,
        output_parameters,
        output_states,
        output_chi_squares,
        output_n_iterations);

    fi.fit(static_cast<ModelID>(model_id));

    return ReturnState::OK;
}
catch (std::exception & exception)
{
    last_error = exception.what();

    return ReturnState::ERROR;
}
catch (...)
{
    last_error = "Unknown Error";

    return ReturnState::ERROR;
}

char const * cpufit_get_last_error()
{
    return last_error.c_str();
}
