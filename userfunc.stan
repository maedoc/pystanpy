functions {
    real userfunc2(vector theta);
}
data {
  int n;
}
parameters {
    vector[n] theta;
}
model {
    target += userfunc2(theta);
}
