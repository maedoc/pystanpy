data {
  int n;
}
transformed data {
  vector[n] shifts;
  for (i in 1:n) shifts[i] = i - 1;
}
parameters {
    vector[n] theta;
}
model {
    target += sum(square(theta - shifts));
}
