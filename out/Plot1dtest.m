function Plot1dtest(name)
  input=fopen(name, "r");
  [x,~,~]=fscanf(input,"%f",[Inf]);
  fclose(input);
	
  clf reset;
  hold on;
  plot(x(:), zeros(length(x),1),"*");
  legend("hide");
  hold off;
endfunction
