# Technopark Highload WebServer

To build and run:

- cmake .
- make
- ./httpd -n &lt;min_cpus&gt; -x &lt;max_cpus&gt; -p &lt;port&gt; -r "&lt;path_to_root_dir&gt;"

By default:

- min_cpus = <count_of_cores>
- max_cpus = min_cpus * 2
- port = 80
- path_to_root_dir = <current_dir>

You should use root user (sudo) to bind port 80.