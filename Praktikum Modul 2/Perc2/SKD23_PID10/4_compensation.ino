float deadzoneCompensator(float inputSerial){
  float diamTolerance = 4;
  float inputCompensated;
  if(inputSerial < ((-1)*diamTolerance)){
    inputCompensated = (minimumTerdeteksiNegatif)+((inputSerial-(diamTolerance))/((-100)-0))*((-100)-(minimumTerdeteksiNegatif));
  }
  else if (inputSerial > diamTolerance){
    inputCompensated = (minimumTerdeteksiPositif)+((inputSerial-(diamTolerance))/((100)-0))*((100)-(minimumTerdeteksiPositif));
  }
  else{
    inputCompensated = 0;
  }
  return inputCompensated;
}
