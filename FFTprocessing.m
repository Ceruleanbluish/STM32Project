delete(instrfind);
clear all
clc

DATA_SIZE = 1024; % length of sampled signal
fs = 2048; % sampling frequency
n = 0:DATA_SIZE-1;
t = n/fs;

ser = serial('COM13', 'BaudRate',115200, 'Timeout',10); % set the serial port
voltage = zeros(DATA_SIZE, 1);
index = 1;
fopen(ser);

% read all of the data
while true
    %for index = n
    tic
    while index <= DATA_SIZE
        temp = fscanf(ser); % read the serial port
        if size(temp) == [0][0]
            disp 'Timeout Occurs'
            disp 'Check Connections'
            break
        else
            voltage(index) = str2double(temp); % convert the data style
            index = index+1;
        end
    end
    toc
    index = 1;
    
    y = fft(voltage,DATA_SIZE); % fast fourier transform
    mag = abs(y)/DATA_SIZE*2; % convert to practical amplitude
    mag(1) = mag(1)/2; % dc component should half
    f = n*fs/DATA_SIZE; % calculate the frequency
    
    % plot the fft figure
    %subplot(2,1,1),
    %plot(f,mag); % remove negative frequency component
    plot(f(1:DATA_SIZE/2),mag(1:DATA_SIZE/2)); % remove negative frequency component
    xlabel('Frequency / Hz');
    ylabel('Magnitude / V');
    title('Fourier Transform of sampled data');
    axis tight;
    
    mag(1) = 0; % remove the dc component
    [SignalM,SignalF] = max(mag(1:DATA_SIZE/2));
    %SignalF
    speed = (3*SignalF)/(2*10.587*10) % output the speed
    pause(0.001);
end

fclose(ser);
delete(ser);
clear ser;
clear all;
clc;
