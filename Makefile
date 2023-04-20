sdv.up:
	@xhost +
	@docker start sdv
sdv.down:
	@xhost +
	@docker stop sdv
sdv.restart:
	@xhost +
	@docker restart sdv
sdv.shell:
	@xhost +	
	@docker exec -it sdv bash
sdv.build:
	@docker build -t sdv ./
# sdv.intelcreate:
# 	@./runROS2Intel.bash