function x=plotCorrelation(name, out="")
  input=fopen(name, "r");
  [x,~,~]=fscanf(input,"%f %f",[2,Inf]);
  fclose(input);

  clf reset;
  hold on;
  hist(x(2,:), 100)
  plot(x(1,2:end), x(2,1:end-1),"*");
  legend("hide");
  print(out, "-dtikz");
  hold off;
endfunction
