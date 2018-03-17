/*
Copyright (c) 2015, Kripasindhu Sarkar
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holder(s) nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/** \brief Example of the usage of local 2d pipeline with simple ransac based pose detector
   *
   * \author Kripasindhu Sarkar
   *
   */

#include "detectors/local2D/training/ODCADRecogTrainerSnapshotBased.h"
#include "detectors/local2D/detection/ODCADRecognizer2DLocal.h"
#include "common/utils/ODFrameGenerator.h"

#include "common/pipeline/ObjectDetector.h"
#include "common/pipeline/ODDetection.h"
#include "detectors/local2D/ODImageLocalMatching.h"


using namespace od;

int main(int argc, char *argv[])
{
  std::string training_input_dir(argv[1]), trained_data_dir(argv[2]);

  //trainer
  od::l2d::ODCADRecogTrainerSnapshotBased *trainer = new od::l2d::ODCADRecogTrainerSnapshotBased(training_input_dir, trained_data_dir);
  //trainer->train();
  cout <<"od_image_cadrecog_camera.cpp: trainer is created!"<<endl;

  //detector
  od::l2d::ODCADRecognizer2DLocal *detector = new od::l2d::ODCADRecognizer2DLocal(trained_data_dir);
  //set commandline options type inputs
  // detector->parseParameterString("--use_gpu --fast --method=1 --error=2 --confidence=0.9 --iterations=500 --inliers=20 --metainfo");
  detector->parseParameterString("--fast --method=1 --error=2 --confidence=0.9 --iterations=500 --inliers=20 --metainfo");
  // detector->setCameraIntrinsicFile("image_local_scenes/camera_webcam_fixed.xml");   //set some other inputs
  detector->setCameraIntrinsicFile("../../../config/webcam.xml");   //set some other inputs
  detector->init();
  cout <<"od_image_cadrecog_camera.cpp: after initialization!"<<endl; 

  //get scenes
  od::ODFrameGenerator<od::ODSceneImage, od::GENERATOR_TYPE_DEVICE> frameGenerator(0);
  //GUI
  cv::namedWindow("Overlay", cv::WINDOW_NORMAL);
  while(frameGenerator.isValid() && cv::waitKey(30) != 27)
  {
    od::ODSceneImage * scene = frameGenerator.getNextFrame();
    cout <<"od_image_cadrecog_camera.cpp: obtain image from webcamera !"<<endl; 
    cv::imshow("Overlay", scene->getCVImage());
    cv::waitKey(200);
    //Detect
    ODDetections3D *detections =  detector->detectOmni(scene);
    cout <<"od_image_cadrecog_camera.cpp: after detectOmni!"<<endl;

    if(detections->size() > 0)
      cv::imshow("Overlay", detections->getMetainfoImage());
    else
      cv::imshow("Overlay", scene->getCVImage());
  }

  return 0;
}