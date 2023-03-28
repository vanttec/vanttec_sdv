sdv.up: display_enable
	@docker start sdv
sdv.down: display_enable
	@docker stop sdv
sdv.restart: display_enable
	@docker restart sdv
sdv.shell: display_enable
	@docker exec -it sdv bash
sdv.intelcreate:
	@./runROS2Intel.bash
display_enable:
	@xhost +
