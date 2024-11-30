#include "controller.h"
#include <cmath>

Controller::Controller(){
  a_x_ = 0;
  f_x_ = 0;
  g_x_ = 0;
  u_aux_ = 0;
  u_aux_dot_ = 0;
  m_ = 0;
  nu_ = 0;
  D_ = 0;
  
  id = 0;
  re_init();
}

SDVOuput Controller::update(const  SDVUpdate &params)
{
  return SDVOutput();
}