package com.proyecto.carrito.Security;

import org.springframework.stereotype.Service;

import com.proyecto.carrito.repository.ClienteRespository;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import com.proyecto.carrito.model.Cliente;


@Service
public class UserDetailServiceImpl implements UserDetailsService {

	@Autowired
	private ClienteRespository userRepository;

	@Override
	public UserDetails loadUserByUsername(String email) throws UsernameNotFoundException {
		Cliente cliente=userRepository
		  .findOneByEmail(email)
		  .orElseThrow(() -> new UsernameNotFoundException("El usuario con email" + email + "no existe"));
		  
		  
		  return new UserDetailsImpl(cliente);
	}
	
	
	
	
	
}
