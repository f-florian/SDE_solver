function plotPoints(name, out="")
  input=fopen(name, "r");
  [x,~,~]=fscanf(input,"%f",Inf);
  fclose(input);
  length(x)
  ## x=min(x,2);
  
  clf reset;
  hold on;
  hist(x, 100)
  legend("hide");
  print(out, "-dtikz");
  hold off;
endfunction
