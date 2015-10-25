chars = ("a".."z").to_a
10000.times do
  name = ""
  rand(1..10).times do
    name << chars.sample * rand(1..3)
  end
  File.open("archive/#{name}", "w")
end

`for file in archive/* do 1 ar r arch.a $file`
