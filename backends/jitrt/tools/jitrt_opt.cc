// Copyright 2021 The TensorFlow Runtime Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//===- JitRT-Opt utility --------------------------------------------------===//
//
// Load MLIR and apply required passes on it.

#include "mlir/Tools/mlir-opt/MlirOptMain.h"
#include "tfrt/init_tfrt_dialects.h"
#include "tfrt/jitrt/conversion/rt_passes.h"
#include "tfrt/jitrt/custom_calls/custom_call_testlib.h"
#include "tfrt/jitrt/jitrt_compiler.h"
#include "tfrt/jitrt/transforms/codegen_passes.h"
#include "third_party/tensorflow/compiler/xla/mlir/transforms/runtime/passes.h"

int main(int argc, char **argv) {
  mlir::DialectRegistry registry;
  tfrt::RegisterTFRTCompiledDialects(registry);
  tfrt::jitrt::RegisterDefaultJitRtDialects(registry);
  tfrt::jitrt::registerRuntimeConversionPasses();
  tfrt::jitrt::registerCodegenTransformsPasses();
  xla::runtime::registerRuntimeTransformsPasses();

  // Test-only dialect for testing custom calls encoding.
  registry.insert<tfrt::jitrt::TestlibDialect>();

  return failed(mlir::MlirOptMain(argc, argv, "JITRT pass driver\n", registry));
}
