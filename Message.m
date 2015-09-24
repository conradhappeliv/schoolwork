function [ m ] = Message()

    [m, Fs] = audioread('name.m4a');
    m = m(:,1);
    Length= length(m);
    t = (0: Length-1)/Fs;

    m = sin(2*pi*40*t);

    %message = sin(2*pi*40*t);
    %x = sin(2*pi*40*t) .* sin(2*pi*80*t) .* sin(2*pi*440*t) .* sin(2*pi*880*t) .* sin(2*pi*4000*t);
    %x = square(t*40);
    %x = sin(40*t) .* cos(60*t);
    

    
    m = transpose(m);
    plot(t,m);
    m = transpose(m);
    M= fftshift(fft(m,Length));
    M_mag= abs(M);
    df=(-Length/2:Length/2-1)*Fs/Length
    plot(df, M_mag);

end
