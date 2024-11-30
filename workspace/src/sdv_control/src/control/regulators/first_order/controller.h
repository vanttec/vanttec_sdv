#ifndef CONTROLLER_H
#define CONTROLLER_H

struct SDVUpdate {
  double f_x{0};
  double g_x{0};
  double nu{0};
  double u_aux{0};
};

struct SDVOuput {
  double huh{0};
};

class Controller  {
 private:
  double a_x_{0};
  double f_x_{0}, g_x_{0};
  double u_aux_{0}, u_aux_dot_{0};
  double m_{0};
  double nu_{0};
  double D_{0};

 public:
  Controller();
  SDVOuput update(const SDVUpdate &params);
};

#endif  // CONTROLLER_H
