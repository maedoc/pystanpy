// Code generated by stanc v2.28.1
#include <stan/model/model_header.hpp>
namespace userfunc_model_namespace {

using stan::io::dump;
using stan::model::assign;
using stan::model::index_uni;
using stan::model::index_max;
using stan::model::index_min;
using stan::model::index_min_max;
using stan::model::index_multi;
using stan::model::index_omni;
using stan::model::model_base_crtp;
using stan::model::rvalue;
using namespace stan::math;


stan::math::profile_map profiles__;
static constexpr std::array<const char*, 5> locations_array__ = 
{" (found before start of program)",
 " (in 'userfunc.stan', line 8, column 4 to column 20)",
 " (in 'userfunc.stan', line 11, column 4 to column 31)",
 " (in 'userfunc.stan', line 5, column 2 to column 8)",
 " (in 'userfunc.stan', line 8, column 11 to column 12)"};


template <typename T0__>
stan::promote_args_t<stan::value_type_t<T0__>>
userfunc2(const T0__& theta_arg__, std::ostream* pstream__) ;

namespace callpy {

#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "object.h"
#include "pyhash.h"
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>
#include <math.h>

void foo(int n, const double *x, double *c_lp, double *c_glp) {
  Py_Initialize();
	PyGILState_STATE gstate;
	gstate = PyGILState_Ensure();
	_import_array();

  // TODO from env var etc
  PyObject *name = PyUnicode_DecodeFSDefault("model");
	PyObject *main = PyImport_Import(name);
  Py_DECREF(name);

	npy_intp shape[1] = {n};
	PyObject *np_x = PyArray_SimpleNewFromData(1, shape, NPY_DOUBLE, (void*) x);

  PyObject *lp = PyObject_GetAttrString(main, "lp");
  PyObject_CallFunctionObjArgs(lp, np_x, NULL);

  // TODO convert from Tuple object
  PyArrayObject *lp_val ;
  PyArray_ScalarAsCtype((PyObject*) lp_val, (void*) c_lp);
  Py_DECREF(lp);
  Py_DECREF(lp_val);

  PyArrayObject *glp_val = (PyArrayObject*) PyObject_CallFunctionObjArgs(glp, np_x, NULL);
  double *c_glp_val = (double*) PyArray_DATA(glp_val);
  for (int i=0; i<n; i++) {
    c_glp[i] = c_glp_val[i];
  }
  Py_DECREF(glp);
  Py_DECREF(glp_val);

	PyGILState_Release(gstate);
}

}

template <typename T0__>
typename boost::math::tools::promote_args<T0__>::type
userfunc2(const Eigen::Matrix<T0__, Eigen::Dynamic, 1>& theta, std::ostream* pstream__) {
	throw std::logic_error("not implemented");
}

template <> double userfunc2(const Eigen::Matrix<double, -1, 1>& theta, std::ostream* pstream__) {
	double out;
	callpy::foo(theta.rows(), theta.data(), &out, NULL);
	return out;
}

template <> var userfunc2(const Eigen::Matrix<var, -1, 1>& theta, std::ostream* pstream__) {
    const Eigen::Matrix<double, -1, 1> theta_val = value_of(theta);
    double fa;
    std::vector<double> glp(theta.rows());
    callpy::foo(theta.rows(), theta_val.data(), &fa, glp.data());
    return precomputed_gradients(fa, theta, glp);
}

class userfunc_model final : public model_base_crtp<userfunc_model> {

 private:
  int n; 
  
 
 public:
  ~userfunc_model() { }
  
  inline std::string model_name() const final { return "userfunc_model"; }

  inline std::vector<std::string> model_compile_info() const noexcept {
    return std::vector<std::string>{"stanc_version = stanc3 v2.28.1", "stancflags = --allow-undefined userfunc.hpp"};
  }
  
  
  userfunc_model(stan::io::var_context& context__,
                 unsigned int random_seed__ = 0,
                 std::ostream* pstream__ = nullptr) : model_base_crtp(0) {
    int current_statement__ = 0;
    using local_scalar_t__ = double ;
    boost::ecuyer1988 base_rng__ = 
        stan::services::util::create_rng(random_seed__, 0);
    (void) base_rng__;  // suppress unused var warning
    static constexpr const char* function__ = "userfunc_model_namespace::userfunc_model";
    (void) function__;  // suppress unused var warning
    local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
    (void) DUMMY_VAR__;  // suppress unused var warning
    try {
      int pos__;
      pos__ = std::numeric_limits<int>::min();
      
      pos__ = 1;
      current_statement__ = 3;
      context__.validate_dims("data initialization","n","int",
           std::vector<size_t>{});
      n = std::numeric_limits<int>::min();
      
      current_statement__ = 3;
      n = context__.vals_i("n")[(1 - 1)];
      current_statement__ = 4;
      validate_non_negative_index("theta", "n", n);
    } catch (const std::exception& e) {
      stan::lang::rethrow_located(e, locations_array__[current_statement__]);
    }
    num_params_r__ = n;
    
  }
  
  template <bool propto__, bool jacobian__ , typename VecR, typename VecI, 
  stan::require_vector_like_t<VecR>* = nullptr, 
  stan::require_vector_like_vt<std::is_integral, VecI>* = nullptr> 
  inline stan::scalar_type_t<VecR> log_prob_impl(VecR& params_r__,
                                                 VecI& params_i__,
                                                 std::ostream* pstream__ = nullptr) const {
    using T__ = stan::scalar_type_t<VecR>;
    using local_scalar_t__ = T__;
    T__ lp__(0.0);
    stan::math::accumulator<T__> lp_accum__;
    stan::io::deserializer<local_scalar_t__> in__(params_r__, params_i__);
    int current_statement__ = 0;
    local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
    (void) DUMMY_VAR__;  // suppress unused var warning
    static constexpr const char* function__ = "userfunc_model_namespace::log_prob";
    (void) function__;  // suppress unused var warning
    
    try {
      Eigen::Matrix<local_scalar_t__, -1, 1> theta;
      theta = Eigen::Matrix<local_scalar_t__, -1, 1>(n);
      stan::math::fill(theta, DUMMY_VAR__);
      
      current_statement__ = 1;
      theta = in__.template read<Eigen::Matrix<local_scalar_t__, -1, 1>>(n);
      {
        current_statement__ = 2;
        lp_accum__.add(userfunc2(theta, pstream__));
      }
    } catch (const std::exception& e) {
      stan::lang::rethrow_located(e, locations_array__[current_statement__]);
    }
    lp_accum__.add(lp__);
    return lp_accum__.sum();
    } // log_prob_impl() 
    
  template <typename RNG, typename VecR, typename VecI, typename VecVar, 
  stan::require_vector_like_vt<std::is_floating_point, VecR>* = nullptr, 
  stan::require_vector_like_vt<std::is_integral, VecI>* = nullptr, 
  stan::require_std_vector_vt<std::is_floating_point, VecVar>* = nullptr> 
  inline void write_array_impl(RNG& base_rng__, VecR& params_r__,
                               VecI& params_i__, VecVar& vars__,
                               const bool emit_transformed_parameters__ = true,
                               const bool emit_generated_quantities__ = true,
                               std::ostream* pstream__ = nullptr) const {
    using local_scalar_t__ = double;
    stan::io::deserializer<local_scalar_t__> in__(params_r__, params_i__);
    stan::io::serializer<local_scalar_t__> out__(vars__);
    static constexpr bool propto__ = true;
    (void) propto__;
    double lp__ = 0.0;
    (void) lp__;  // dummy to suppress unused var warning
    int current_statement__ = 0; 
    stan::math::accumulator<double> lp_accum__;
    local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
    constexpr bool jacobian__ = false;
    (void) DUMMY_VAR__;  // suppress unused var warning
    static constexpr const char* function__ = "userfunc_model_namespace::write_array";
    (void) function__;  // suppress unused var warning
    
    try {
      Eigen::Matrix<double, -1, 1> theta;
      theta = Eigen::Matrix<double, -1, 1>(n);
      stan::math::fill(theta, std::numeric_limits<double>::quiet_NaN());
      
      current_statement__ = 1;
      theta = in__.template read<Eigen::Matrix<local_scalar_t__, -1, 1>>(n);
      out__.write(theta);
      if (logical_negation((primitive_value(emit_transformed_parameters__) ||
            primitive_value(emit_generated_quantities__)))) {
        return ;
      } 
      if (logical_negation(emit_generated_quantities__)) {
        return ;
      } 
    } catch (const std::exception& e) {
      stan::lang::rethrow_located(e, locations_array__[current_statement__]);
    }
    } // write_array_impl() 
    
  template <typename VecVar, typename VecI, 
  stan::require_std_vector_t<VecVar>* = nullptr, 
  stan::require_vector_like_vt<std::is_integral, VecI>* = nullptr> 
  inline void transform_inits_impl(VecVar& params_r__, VecI& params_i__,
                                   VecVar& vars__,
                                   std::ostream* pstream__ = nullptr) const {
    using local_scalar_t__ = double;
    stan::io::deserializer<local_scalar_t__> in__(params_r__, params_i__);
    stan::io::serializer<local_scalar_t__> out__(vars__);
    int current_statement__ = 0;
    local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
    
    try {
      int pos__;
      pos__ = std::numeric_limits<int>::min();
      
      pos__ = 1;
      Eigen::Matrix<local_scalar_t__, -1, 1> theta;
      theta = Eigen::Matrix<local_scalar_t__, -1, 1>(n);
      stan::math::fill(theta, DUMMY_VAR__);
      
      for (int sym1__ = 1; sym1__ <= n; ++sym1__) {
        assign(theta, in__.read<local_scalar_t__>(),
          "assigning variable theta", index_uni(sym1__));
      }
      out__.write(theta);
    } catch (const std::exception& e) {
      stan::lang::rethrow_located(e, locations_array__[current_statement__]);
    }
    } // transform_inits_impl() 
    
  inline void get_param_names(std::vector<std::string>& names__) const {
    
    names__ = std::vector<std::string>{"theta"};
    
    } // get_param_names() 
    
  inline void get_dims(std::vector<std::vector<size_t>>& dimss__) const {
    
    dimss__ = std::vector<std::vector<size_t>>{std::vector<size_t>{
                                                                   static_cast<size_t>(n)
                                                                   }};
    
    } // get_dims() 
    
  inline void constrained_param_names(
                                      std::vector<std::string>& param_names__,
                                      bool emit_transformed_parameters__ = true,
                                      bool emit_generated_quantities__ = true) const
    final {
    
    for (int sym1__ = 1; sym1__ <= n; ++sym1__) {
      {
        param_names__.emplace_back(std::string() + "theta" + '.' + std::to_string(sym1__));
      } 
    }
    if (emit_transformed_parameters__) {
      
    }
    
    if (emit_generated_quantities__) {
      
    }
    
    } // constrained_param_names() 
    
  inline void unconstrained_param_names(
                                        std::vector<std::string>& param_names__,
                                        bool emit_transformed_parameters__ = true,
                                        bool emit_generated_quantities__ = true) const
    final {
    
    for (int sym1__ = 1; sym1__ <= n; ++sym1__) {
      {
        param_names__.emplace_back(std::string() + "theta" + '.' + std::to_string(sym1__));
      } 
    }
    if (emit_transformed_parameters__) {
      
    }
    
    if (emit_generated_quantities__) {
      
    }
    
    } // unconstrained_param_names() 
    
  inline std::string get_constrained_sizedtypes() const {
    
    return std::string("[{\"name\":\"theta\",\"type\":{\"name\":\"vector\",\"length\":" + std::to_string(n) + "},\"block\":\"parameters\"}]");
    
    } // get_constrained_sizedtypes() 
    
  inline std::string get_unconstrained_sizedtypes() const {
    
    return std::string("[{\"name\":\"theta\",\"type\":{\"name\":\"vector\",\"length\":" + std::to_string(n) + "},\"block\":\"parameters\"}]");
    
    } // get_unconstrained_sizedtypes() 
    
  
    // Begin method overload boilerplate
    template <typename RNG>
    inline void write_array(RNG& base_rng,
                            Eigen::Matrix<double,Eigen::Dynamic,1>& params_r,
                            Eigen::Matrix<double,Eigen::Dynamic,1>& vars,
                            const bool emit_transformed_parameters = true,
                            const bool emit_generated_quantities = true,
                            std::ostream* pstream = nullptr) const {
      const size_t num_params__ = n;
      const size_t num_transformed = 0;
      const size_t num_gen_quantities = 0;
      std::vector<double> vars_vec(num_params__
       + (emit_transformed_parameters * num_transformed)
       + (emit_generated_quantities * num_gen_quantities));
      std::vector<int> params_i;
      write_array_impl(base_rng, params_r, params_i, vars_vec,
          emit_transformed_parameters, emit_generated_quantities, pstream);
      vars = Eigen::Map<Eigen::Matrix<double,Eigen::Dynamic,1>>(
        vars_vec.data(), vars_vec.size());
    }

    template <typename RNG>
    inline void write_array(RNG& base_rng, std::vector<double>& params_r,
                            std::vector<int>& params_i,
                            std::vector<double>& vars,
                            bool emit_transformed_parameters = true,
                            bool emit_generated_quantities = true,
                            std::ostream* pstream = nullptr) const {
      const size_t num_params__ = n;
      const size_t num_transformed = 0;
      const size_t num_gen_quantities = 0;
      vars.resize(num_params__
        + (emit_transformed_parameters * num_transformed)
        + (emit_generated_quantities * num_gen_quantities));
      write_array_impl(base_rng, params_r, params_i, vars, emit_transformed_parameters, emit_generated_quantities, pstream);
    }

    template <bool propto__, bool jacobian__, typename T_>
    inline T_ log_prob(Eigen::Matrix<T_,Eigen::Dynamic,1>& params_r,
                       std::ostream* pstream = nullptr) const {
      Eigen::Matrix<int, -1, 1> params_i;
      return log_prob_impl<propto__, jacobian__>(params_r, params_i, pstream);
    }

    template <bool propto__, bool jacobian__, typename T__>
    inline T__ log_prob(std::vector<T__>& params_r,
                        std::vector<int>& params_i,
                        std::ostream* pstream = nullptr) const {
      return log_prob_impl<propto__, jacobian__>(params_r, params_i, pstream);
    }


    inline void transform_inits(const stan::io::var_context& context,
                         Eigen::Matrix<double, Eigen::Dynamic, 1>& params_r,
                         std::ostream* pstream = nullptr) const final {
      std::vector<double> params_r_vec(params_r.size());
      std::vector<int> params_i;
      transform_inits(context, params_i, params_r_vec, pstream);
      params_r = Eigen::Map<Eigen::Matrix<double,Eigen::Dynamic,1>>(
        params_r_vec.data(), params_r_vec.size());
    }

  inline void transform_inits(const stan::io::var_context& context,
                              std::vector<int>& params_i,
                              std::vector<double>& vars,
                              std::ostream* pstream__ = nullptr) const {
     constexpr std::array<const char*, 1> names__{"theta"};
      const std::array<Eigen::Index, 1> constrain_param_sizes__{n};
      const auto num_constrained_params__ = std::accumulate(
        constrain_param_sizes__.begin(), constrain_param_sizes__.end(), 0);
    
     std::vector<double> params_r_flat__(num_constrained_params__);
     Eigen::Index size_iter__ = 0;
     Eigen::Index flat_iter__ = 0;
     for (auto&& param_name__ : names__) {
       const auto param_vec__ = context.vals_r(param_name__);
       for (Eigen::Index i = 0; i < constrain_param_sizes__[size_iter__]; ++i) {
         params_r_flat__[flat_iter__] = param_vec__[i];
         ++flat_iter__;
       }
       ++size_iter__;
     }
     vars.resize(num_params_r__);
     transform_inits_impl(params_r_flat__, params_i, vars, pstream__);
    } // transform_inits() 
    
};
}
using stan_model = userfunc_model_namespace::userfunc_model;

#ifndef USING_R

// Boilerplate
stan::model::model_base& new_model(
        stan::io::var_context& data_context,
        unsigned int seed,
        std::ostream* msg_stream) {
  stan_model* m = new stan_model(data_context, seed, msg_stream);
  return *m;
}

stan::math::profile_map& get_stan_profile_data() {
  return userfunc_model_namespace::profiles__;
}

#endif


