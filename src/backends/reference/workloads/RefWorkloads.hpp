//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include "Activation.hpp"
#include "BatchNormImpl.hpp"
#include "ConvImpl.hpp"
#include "Concatenate.hpp"
#include "ElementwiseFunction.hpp"
#include "FullyConnected.hpp"
#include "Gather.hpp"
#include "Pooling2d.hpp"
#include "RefActivationWorkload.hpp"
#include "RefBatchNormalizationWorkload.hpp"
#include "RefBatchToSpaceNdWorkload.hpp"
#include "RefConvolution2dWorkload.hpp"
#include "RefConstantWorkload.hpp"
#include "RefConcatWorkload.hpp"
#include "RefConvertFp16ToFp32Workload.hpp"
#include "RefConvertFp32ToFp16Workload.hpp"
#include "RefDepthwiseConvolution2dWorkload.hpp"
#include "RefDetectionPostProcessWorkload.hpp"
#include "RefDebugWorkload.hpp"
#include "RefDequantizeWorkload.hpp"
#include "RefElementwiseWorkload.hpp"
#include "RefFullyConnectedWorkload.hpp"
#include "RefFloorWorkload.hpp"
#include "RefFakeQuantizationFloat32Workload.hpp"
#include "RefGatherWorkload.hpp"
#include "RefL2NormalizationWorkload.hpp"
#include "RefLstmWorkload.hpp"
#include "RefMeanWorkload.hpp"
#include "RefNormalizationWorkload.hpp"
#include "RefPooling2dWorkload.hpp"
#include "RefPermuteWorkload.hpp"
#include "RefPadWorkload.hpp"
#include "RefPreluWorkload.hpp"
#include "RefQuantizeWorkload.hpp"
#include "RefResizeBilinearWorkload.hpp"
#include "RefResizeWorkload.hpp"
#include "RefRsqrtWorkload.hpp"
#include "RefReshapeWorkload.hpp"
#include "RefSplitterWorkload.hpp"
#include "RefSoftmaxWorkload.hpp"
#include "RefSpaceToBatchNdWorkload.hpp"
#include "RefStridedSliceWorkload.hpp"
#include "RefSpaceToDepthWorkload.hpp"
#include "RefTransposeConvolution2dWorkload.hpp"
#include "RefWorkloadUtils.hpp"
#include "Resize.hpp"
#include "Softmax.hpp"
#include "Splitter.hpp"
#include "TensorBufferArrayView.hpp"