set_property PACKAGE_PIN AB2 [get_ports top_clk_clk_p]
set_property PACKAGE_PIN D19 [get_ports top_uart_rxd]
set_property PACKAGE_PIN L23 [get_ports top_reset]
set_property PACKAGE_PIN N17 [get_ports top_uart_txd]
set_property PACKAGE_PIN G20 [get_ports {top_gpio_tri_o[1]}]
set_property PACKAGE_PIN N16 [get_ports {top_gpio_tri_o[0]}]

set_property IOSTANDARD DIFF_HSTL_II [get_ports top_clk_clk_p]
set_property IOSTANDARD DIFF_HSTL_II [get_ports top_clk_clk_n]
set_property IOSTANDARD LVCMOS25 [get_ports top_reset]
set_property IOSTANDARD LVCMOS25 [get_ports top_uart_rxd]
set_property IOSTANDARD LVCMOS25 [get_ports top_uart_txd]
set_property IOSTANDARD LVCMOS25 [get_ports {top_gpio_tri_o[1]}]
set_property IOSTANDARD LVCMOS25 [get_ports {top_gpio_tri_o[0]}]